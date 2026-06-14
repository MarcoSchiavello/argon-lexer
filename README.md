<p align="center">
    <img  src=".github/imgs/argon-logo-dark.svg" alt="Argon element tile" height="150">
</p>
<br/>
Argon is a modular C++23 lexer that tokenizes source input through pluggable, per-token generators for easy extension.

Instead of hard-coding the grammar of one language, Argon lets you teach it *your* language by registering small, self-contained **token generators**. Each generator knows how to recognize one kind of token (a number, an operator, a keyword, an identifier, ...) and how to build the corresponding `Token` object. To lex a new language, you write new generators — the lexer core never changes.

> **Very early work in progress.** Argon is in its early stages — supported input streams, class layout,
> and the generator contract are all unstable and may change without notice between
> commits. Expect rough edges, missing features, and breaking changes. It's shared for
> learning and experimentation. Feedback and ideas are
> welcome while the design settles.

## How it works

The lexer scans the input character by character, growing a candidate `payload` string. On every step it asks the registered generators whether the current `payload` is still a valid prefix of their token type (`check`). It keeps extending the payload as long as at least one generator accepts it. When no generator can accept any longer sequence, the last matching generator turns the accumulated `payload` into a `Token` via `generate`.

### Core pieces

| Component | File | Responsibility |
|-----------|------|----------------|
| `Lexer` | `include/lexer.hpp`, `src/lexer.cpp` | Walks the input, skips whitespace/newlines, drives generators, emits tokens. |
| `ITokenGenerator` | `include/generators/iTokenGenerator.hpp` | Interface every generator implements: `check()` + `generate()`. |
| `Token` | `include/tokens/token.hpp` | Base token: holds an `id` and a `label`, renders as `<id,label>`. |

### The generator contract

```cpp
class ITokenGenerator {
public:
    virtual ~ITokenGenerator() = default;

    // Is `payload` a valid (complete or partial) sequence for this token type?
    // Called repeatedly as the lexer appends one more character each step.
    [[nodiscard]] virtual bool check(const std::string& payload) const = 0;

    // Build the Token from the final accepted payload.
    [[nodiscard]] virtual std::shared_ptr<Token> generate(const std::string& payload) const = 0;
};
```

> ⚠️ **`check` runs on every single character.** The lexer appends one character at a
> time and calls `check` again on the full accumulated `payload` each step. Avoid if 
> not necessary re-validating the entire payload from scratch every call. A possible solution 
> could be to only check the newly added character 
> (e.g. inspect `payload.back()` instead of looping over the
> whole string) — otherwise lexing a token becomes O(n² * m) where n=token length and m=number of generators.
> 
> this design might change in the future due to the fact that this project is work in progress, in the future
> is possible that the correct use is more incentivised or forced by the structure or arguments of check()

## Build & run

Requires CMake ≥ 3.20 and a C++23 compiler.

```sh
cmake -B build
cmake --build build
./build/argon        # Windows: .\build\argon.exe
```

The bundled `main.cpp` lexes a small arithmetic string and prints each token:

```cpp
auto lexer = std::make_unique<Lexer>("34321315+41231233+23131312");
lexer->addTokenGenerator(std::make_shared<IntTokenGenerator>());
lexer->addTokenGenerator(std::make_shared<AdditionTokenGenerator>());

std::shared_ptr<Token> token;
while ((token = lexer->lexToken()) != nullptr) {
    std::cout << token->toString() << std::endl;
}
```

Output:

```
<256,INT,34321315>
<1,+>
<256,INT,41231233>
<1,+>
<256,INT,23131312>
```

---

## Tokenizing your own language

Adding support for new syntax is a three-step pattern: **(1)** give the token an id, **(2)** write a generator, **(3)** register it. Below we add a `-` (subtraction) operator.

**Step 1. Add an id** in `include/tokenId.hpp`:

```cpp
enum TokenId {
    ADDITION    = 1,
    SUBTRACTION = 2,   // <-- new
    NUMBER      = 256
};
```

but, if you use Argon as a library you can define your own enum that maps int ids and reference them in your generators
and leave TokenId enum as a library internal for build-in tokens

**Step 2. Declare the generator** — `include/generators/subtractionTokenGenerator.hpp`:

```cpp
#pragma once

#include "iTokenGenerator.hpp"
#include "tokenId.hpp"

class SubtractionTokenGenerator : public ITokenGenerator {
public:
    ~SubtractionTokenGenerator() override = default;
    [[nodiscard]] bool check(const std::string& payload) const override;
    [[nodiscard]] std::shared_ptr<Token> generate(const std::string& payload) const override;
};
```

**Implement it** — `src/generators/subtractionTokenGenerator.cpp`:

```cpp
#include "subtractionTokenGenerator.hpp"

bool SubtractionTokenGenerator::check(const std::string& payload) const {
    return payload == "-";          // only a lone '-' is valid
}

std::shared_ptr<Token> SubtractionTokenGenerator::generate(const std::string& payload) const {
    return std::make_shared<Token>(SUBTRACTION, payload);
}
```

**Step 3. Register it** in `main.cpp`:

```cpp
#include "subtractionTokenGenerator.hpp"

lexer->addTokenGenerator(std::make_shared<IntTokenGenerator>());
lexer->addTokenGenerator(std::make_shared<AdditionTokenGenerator>());
lexer->addTokenGenerator(std::make_shared<SubtractionTokenGenerator>());   // new
```

Rebuild, and the lexer now understands your extended language.