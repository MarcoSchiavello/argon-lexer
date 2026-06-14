#pragma once

#include <memory>
#include <set>
#include <string>
#include <typeindex>

#include "token.hpp"
#include "iTokenGenerator.hpp"

// Comparator: orders by the concrete (runtime) type of each generator
struct TokenGeneratorByType {
    bool operator()(const std::shared_ptr<ITokenGenerator>& a,
                    const std::shared_ptr<ITokenGenerator>& b) const {
        return std::type_index(typeid(*a)) < std::type_index(typeid(*b));
    }
};

class Lexer {
    public:
        explicit Lexer(const std::string&);
        std::shared_ptr<Token> lexToken();
        void addTokenGenerator(std::shared_ptr<ITokenGenerator>);

    private:
        int m_lineNumber;
        std::string m_text;
        std::string::iterator m_iterator;
        std::set<std::shared_ptr<ITokenGenerator>, TokenGeneratorByType> m_tokenGens;

        void skipFiller();
};