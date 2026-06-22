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
        char m_peek;
        int m_iteratorLookAhead;
        bool m_closeToken;
        std::string m_text;
        std::string::iterator m_iterator;
        std::set<std::unique_ptr<ITokenGenerator>> m_tokenGens;
        const ICommentState* m_commentState;

        void skipFiller();
        void advance(std::string&);
        void advance();
        void commit();
        bool isFinished();
        [[nodiscard]] std::set<ITokenGenerator*> prepareCandidates() const;
};