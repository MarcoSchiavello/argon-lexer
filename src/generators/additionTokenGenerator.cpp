#include "additionTokenGenerator.hpp"

bool AdditionTokenGenerator::check(const char peek, const std::string& payload) const {
    return peek + payload == "+";
}

bool AdditionTokenGenerator::accept(const std::string& payload) const {
    return payload.size() == 1 && payload.at(0) == '+';
}


std::unique_ptr<Token> AdditionTokenGenerator::generate(const std::string& payload) const {
    return std::make_unique<Token>(ADDITION, payload);
}

