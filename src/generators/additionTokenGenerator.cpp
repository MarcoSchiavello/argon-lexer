#include "additionTokenGenerator.hpp"

bool AdditionTokenGenerator::check(const std::string& payload) const {
    return payload == "+";
}

std::shared_ptr<Token> AdditionTokenGenerator::generate(const std::string& payload) const {
    return std::make_shared<Token>(ADDITION, payload);
}

