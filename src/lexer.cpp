#include "lexer.hpp"

Lexer::Lexer(const std::string& text) {
    m_lineNumber = 0;
    m_text = text;
    m_iterator = m_text.begin();
    m_peek = *m_iterator;
}

void Lexer::skipFiller() {
    while  (*m_iterator == ' ' || *m_iterator == '\n') {
        if (*m_iterator == '\n') {
            m_lineNumber++;
        }

        ++m_iterator;
    }

    m_peek = *m_iterator;
}

void Lexer::advance(std::string& payload) {
    payload += m_peek;
    ++m_iterator;
    m_peek = *m_iterator;
}

bool Lexer::isFinished() {
    return m_iterator == m_text.end();
}

void Lexer::addTokenGenerator(std::shared_ptr<ITokenGenerator> gen) {
    m_tokenGens.emplace(std::move(gen));
}

std::shared_ptr<Token> Lexer::lexToken() {
    if (isFinished()) {
        return nullptr;
    }

    skipFiller();

    auto candidates = m_tokenGens;
    bool validSeq;
    std::string payload;
    std::shared_ptr<ITokenGenerator> lastFailedGen = nullptr;

    do {
        validSeq = false;
        for (auto gen_itr = candidates.begin(); gen_itr != candidates.end();) {
            auto& gen = *gen_itr;

            if (gen->check(payload + m_peek)) {
                validSeq = true;
                advance(payload);

                // If next character is the end of content, then flag it as failed gen so it
                // will close the sequence and selected to generate the token
                if (!isFinished()) {
                    ++gen_itr;
                    continue;
                }
            }

            lastFailedGen = *gen_itr;
            gen_itr = candidates.erase(gen_itr);
        }
    } while(validSeq && !isFinished());

    return lastFailedGen->generate(payload);
}