#pragma once

#include <memory>
#include <string>
#include <vector>

#include "lexer.hpp"
#include "intTokenGenerator.hpp"
#include "additionTokenGenerator.hpp"
#include "divisionTokenGenerator.hpp"

namespace argon::test {

inline std::vector<std::string> lexAll(const std::string& input) {
    Lexer lexer(input);
    lexer.addTokenGenerator(std::make_unique<IntTokenGenerator>())
         .addTokenGenerator(std::make_unique<AdditionTokenGenerator>())
         .addTokenGenerator(std::make_unique<DivisionTokenGenerator>());

    std::vector<std::string> tokens;
    std::unique_ptr<Token> token;
    while ((token = lexer.lexToken()) != nullptr) {
        tokens.push_back(token->toString());
    }
    return tokens;
}

inline std::string lexJoined(const std::string& input) {
    std::string joined;
    for (const auto& token : lexAll(input)) {
        if (!joined.empty()) joined += ' ';
        joined += token;
    }
    return joined;
}

inline const std::string PLUS = "<1,+>";
inline const std::string SLASH = "<3,/>";
inline std::string INT(const int value) { return "<256,INT," + std::to_string(value) + ">"; }

}
