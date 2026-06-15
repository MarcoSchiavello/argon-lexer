#pragma once

#include <memory>
#include "token.hpp"

class ITokenGenerator {
    public:
        virtual ~ITokenGenerator() = default;
        [[nodiscard]] virtual bool check(char peek, const std::string& payload) const = 0;
        [[nodiscard]] virtual std::unique_ptr<Token> generate(const std::string& payload) const = 0;
};

