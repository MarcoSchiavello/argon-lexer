#include <vector>
#include <memory>
#include <iostream>
#include "token.hpp"
#include "lexer.hpp"
#include "intTokenGenerator.hpp"
#include "additionTokenGenerator.hpp"


int main() {
    auto collectedToken = std::vector<std::shared_ptr<Token>>();
    const auto lexer = std::make_unique<Lexer>("34321315+   \n 41231233+23131312+21313++");
    lexer->addTokenGenerator(std::make_shared<IntTokenGenerator>());
    lexer->addTokenGenerator(std::make_shared<AdditionTokenGenerator>());

    std::shared_ptr<Token> token;
    while ((token = lexer->lexToken()) != nullptr) {
        collectedToken.push_back(token);
        std::cout << token->toString() << std::endl;
    }
}