#include "divisionTokenGenerator.hpp"

bool DivisionTokenGenerator::check(const char peek, const std::string& payload) const {
    return peek + payload == "/";
}

std::unique_ptr<Token> DivisionTokenGenerator::generate(const std::string& payload) const {
    return std::make_unique<Token>(ADDITION, payload);
}

