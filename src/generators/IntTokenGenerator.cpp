#include "intTokenGenerator.hpp"

bool IntTokenGenerator::check(const char peek, const std::string& payload) const {
    return Utils::isDigit(peek);
}

std::shared_ptr<Token> IntTokenGenerator::generate(const std::string& payload) const {
    return std::make_shared<NumericToken<int>>(NUMBER, "INT", std::stoi(payload));
}
