<p align="center">
    <img  src=".github/imgs/argon-logo-dark.svg" alt="Argon element tile" height="200">
</p>
<br/>
Argon is a modular C++23 lexer that tokenizes source input through pluggable, per-token generators for easy extension.

Instead of hard-coding the grammar of one language, Argon lets you teach it *your* language by registering small, self-contained **token generators**. Each generator knows how to recognize one kind of token (a number, an operator, a keyword, an identifier, ...) and how to build the corresponding `Token` object. To lex a new language you write new generators, and the lexer core never changes.

<details>
<summary><strong>Status: very early work in progress</strong></summary>

Argon is in its early stages. Supported input streams, class layout, and the generator contract are all unstable and may change without notice between commits. Expect rough edges, missing features, and breaking changes. It's shared for learning and experimentation. Feedback and ideas are welcome while the design settles.

</details>

## How it works

The lexer scans the input character by character, growing a candidate `payload` string. On every step it asks the registered generators whether the current `payload`, extended by the next character, is still a valid prefix of their token type (`check`). It keeps extending the payload as long as at least one generator accepts it. When no generator can accept any longer sequence, the last matching generator turns the accumulated `payload` into a `Token` via `generate`.

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

    // Is the current `payload`, extended by the next character `peek`,
    // still a valid (partial or complete) sequence for this token type?
    // Called once per character as the lexer scans.
    [[nodiscard]] virtual bool check(char peek, const std::string& payload) const = 0;

    // Build the Token from the final accepted payload.
    [[nodiscard]] virtual std::unique_ptr<Token> generate(const std::string& payload) const = 0;
};
```

<details>
<summary><strong>Note: <code>check</code> runs once per character</strong></summary>

The lexer feeds the next character as `peek` and passes the payload accumulated so far. Prefer inspecting only the incoming `peek` instead of re-scanning the whole `payload` on every call, otherwise lexing a token becomes O(n² * m), where n is the token length and m is the number of generators.

This may change as the project evolves; a future version might encourage or enforce the incremental approach through the structure or arguments of `check`.

</details>

Generators are registered on the lexer with `addTokenGenerator`, which takes ownership of a `std::unique_ptr<ITokenGenerator>` and returns a `Lexer&` so calls can be chained. Only one generator per concrete type is kept: adding a second generator of a type that is already registered is ignored.

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
lexer->addTokenGenerator(std::make_unique<IntTokenGenerator>())
      .addTokenGenerator(std::make_unique<AdditionTokenGenerator>());

std::unique_ptr<Token> token;
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

## Tokenizing your own language

Adding support for new syntax is a three-step pattern: give the token an id, write a generator, then register it. Below we add a `-` (subtraction) operator.

**Step 1. Add an id** in `include/tokenId.hpp`:

```cpp
enum TokenId {
    ADDITION    = 1,
    SUBTRACTION = 2,   // <-- new
    NUMBER      = 256
};
```

If you use Argon as a library you can instead define your own enum that maps int ids and reference them in your generators, leaving `TokenId` as a library internal for built-in tokens.

**Step 2. Declare the generator** in `include/generators/subtractionTokenGenerator.hpp`:

```cpp
#pragma once

#include "iTokenGenerator.hpp"
#include "tokenId.hpp"

class SubtractionTokenGenerator : public ITokenGenerator {
public:
    ~SubtractionTokenGenerator() override = default;
    [[nodiscard]] bool check(char peek, const std::string& payload) const override;
    [[nodiscard]] std::unique_ptr<Token> generate(const std::string& payload) const override;
};
```

**Implement it** in `src/generators/subtractionTokenGenerator.cpp`:

```cpp
#include "subtractionTokenGenerator.hpp"

bool SubtractionTokenGenerator::check(char peek, const std::string& payload) const {
    return peek + payload == "-";   // only a lone '-' is valid
}

std::unique_ptr<Token> SubtractionTokenGenerator::generate(const std::string& payload) const {
    return std::make_unique<Token>(SUBTRACTION, payload);
}
```

**Step 3. Register it** in `main.cpp`:

```cpp
#include "subtractionTokenGenerator.hpp"

lexer->addTokenGenerator(std::make_unique<IntTokenGenerator>())
      .addTokenGenerator(std::make_unique<AdditionTokenGenerator>())
      .addTokenGenerator(std::make_unique<SubtractionTokenGenerator>());   // new
```

Rebuild, and the lexer now handles the extended language.
