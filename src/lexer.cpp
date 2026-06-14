#include "lexer.hpp"

Lexer::Lexer(const std::string& text) {
    m_lineNumber = 0;
    m_text = text;
    m_iterator = m_text.begin();
}

void Lexer::skipFiller() {
    while  (*m_iterator == ' ' || *m_iterator == '\n') {
        if (*m_iterator == '\n') {
            m_lineNumber++;
        }

        ++m_iterator;
    }
}

void Lexer::addTokenGenerator(std::shared_ptr<ITokenGenerator> gen) {
    m_tokenGens.emplace(std::move(gen));
}

std::shared_ptr<Token> Lexer::lexToken() {
    if (m_iterator == m_text.end()) {
        return nullptr;
    }

    skipFiller();

    auto gens = m_tokenGens;
    gens.clear();
    std::string payload;
    bool validSeq;
    std::shared_ptr<ITokenGenerator> lastFailedGen = nullptr;
    std::shared_ptr<Token> token = nullptr;

    do {
        validSeq = false;
        const char peek = *m_iterator;

        for (const auto& gen : m_tokenGens) {
            if (gens.contains(gen)) {
                continue;
            }

            if (gen->check(payload + peek)) {
                validSeq = true;
                payload += peek;
                ++m_iterator;

                if (m_iterator != m_text.end()) {
                    continue;
                }
            }

            lastFailedGen = gen;
            gens.insert(gen);
        }
    } while(validSeq && m_iterator != m_text.end());

    return lastFailedGen->generate(payload);
}