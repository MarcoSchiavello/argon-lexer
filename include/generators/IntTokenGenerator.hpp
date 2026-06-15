#pragma once

#include "iTokenGenerator.hpp"
#include "numericToken.hpp"
#include "utils.hpp"
#include "tokenId.hpp"

class IntTokenGenerator : public ITokenGenerator {
    public:
        ~IntTokenGenerator() override = default;
        [[nodiscard]]  bool check(char peek, const std::string& payload) const override;
        [[nodiscard]]  std::unique_ptr<Token> generate(const std::string& payload) const override;
};