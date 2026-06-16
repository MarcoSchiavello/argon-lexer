#pragma once

#include "iTokenGenerator.hpp"
#include "tokenId.hpp"

class DivisionTokenGenerator : public ITokenGenerator {
    public:
        ~DivisionTokenGenerator() override = default;
        [[nodiscard]]  bool check(char peek, const std::string& payload) const override;
        [[nodiscard]]  std::unique_ptr<Token> generate(const std::string& payload) const override;
};