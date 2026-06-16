#pragma once

#include <memory>
#include <set>
#include <string>

#include "token.hpp"
#include "iTokenGenerator.hpp"
#include "iCommentState.hpp"
#include "noCommentState.hpp"

class Lexer {
    public:
        explicit Lexer(const std::string&);
        std::unique_ptr<Token> lexToken();
        Lexer& addTokenGenerator(std::unique_ptr<ITokenGenerator>);

    private:
        int m_lineNumber;
        std::string m_text;
        std::string::iterator m_iterator;
        std::set<std::unique_ptr<ITokenGenerator>> m_tokenGens;
        char m_peek;
        std::unique_ptr<ICommentState> m_commentState;

        void skipFiller();
        void advance(std::string&);
        void advance();
        bool isFinished();
        [[nodiscard]] std::set<ITokenGenerator*> prepareCandidates() const;
};