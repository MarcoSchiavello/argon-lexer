#pragma once

#include "iTokenGenerator.hpp"
#include "tokenId.hpp"

class AdditionTokenGenerator : public ITokenGenerator {
    public:
        ~AdditionTokenGenerator() override = default;
        [[nodiscard]]  bool check(char peek, const std::string& payload) const override;
        [[nodiscard]]  bool accept(const std::string& payload) const override;
        [[nodiscard]]  std::unique_ptr<Token> generate(const std::string& payload) const override;
};