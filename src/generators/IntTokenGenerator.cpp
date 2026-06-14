#include "intTokenGenerator.hpp"

bool IntTokenGenerator::check(const std::string& payload) const {
    return Utils::isDigit(payload[payload.length()-1]);
}

std::shared_ptr<Token> IntTokenGenerator::generate(const std::string& payload) const {
    return std::make_shared<NumericToken<int>>(NUMBER, "INT", std::stoi(payload));
}
