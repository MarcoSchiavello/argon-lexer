#include "intTokenGenerator.hpp"

bool IntTokenGenerator::check(const char peek, const std::string& payload) const {
    return Utils::isDigit(peek);
}

bool IntTokenGenerator::accept(const std::string& payload) const {
    return  Utils::isDigit(payload.back());
}

std::unique_ptr<Token> IntTokenGenerator::generate(const std::string& payload) const {
    return std::make_unique<NumericToken<int>>(NUMBER, "INT", std::stoi(payload));
}
