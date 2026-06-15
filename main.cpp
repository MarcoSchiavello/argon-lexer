#include <vector>
#include <memory>
#include <iostream>
#include "token.hpp"
#include "lexer.hpp"
#include "intTokenGenerator.hpp"
#include "additionTokenGenerator.hpp"


int main() {
    auto collectedToken = std::vector<std::unique_ptr<Token>>();
    const auto lexer = std::make_unique<Lexer>("34321315+   \n 41231233+23131312+21313++");
    lexer->addTokenGenerator(std::make_unique<IntTokenGenerator>())
          .addTokenGenerator(std::make_unique<AdditionTokenGenerator>());

    std::unique_ptr<Token> token;
    while ((token = lexer->lexToken()) != nullptr) {
        collectedToken.push_back(std::move(token));
        std::cout << collectedToken.back()->toString() << std::endl;
    }
}