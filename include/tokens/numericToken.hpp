#pragma once

#include "token.hpp"

template <typename T>
class NumericToken : public Token {
    public:
        ~NumericToken() override = default;
        NumericToken(const int id, const std::string& label, T value) : Token(id, label), m_value(value) {}

        std::string toString() override {
            return "<" + std::to_string(getId()) + "," + getLabel() + "," + std::to_string(m_value) + ">";
        }

    private:
        T m_value;
};