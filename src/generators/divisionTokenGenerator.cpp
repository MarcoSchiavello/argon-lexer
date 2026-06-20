#include "divisionTokenGenerator.hpp"

bool DivisionTokenGenerator::check(const char peek, const std::string& payload) const {
    return peek + payload == "/";
}

bool DivisionTokenGenerator::accept(const std::string& payload) const {
    return payload.size() == 1 && payload.at(0) == '/';
}

std::unique_ptr<Token> DivisionTokenGenerator::generate(const std::string& payload) const {
    return std::make_unique<Token>(DIVISION, payload);
}

