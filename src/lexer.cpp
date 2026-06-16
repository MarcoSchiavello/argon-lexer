#include "lexer.hpp"

#include <typeinfo>

Lexer::Lexer(const std::string& text) {
    m_lineNumber = 0;
    m_text = text;
    m_iterator = m_text.begin();
    m_peek = *m_iterator;
    m_commentState = std::unique_ptr<NoCommentState>();
}

void Lexer::skipFiller() {
    while  (m_peek == ' ' || m_peek == '\n' || m_commentState->isSkippable()) {
        if (m_peek == '\n') {
            m_lineNumber++;
        }

        advance();
    }
}

void Lexer::advance(std::string& payload) {
    payload += m_peek;
    advance();
}

void Lexer::advance() {
    ++m_iterator;
    m_peek = *m_iterator;
    if (auto newState = m_commentState->update(m_peek)) {
        m_commentState = std::move(newState);
    }
}

bool Lexer::isFinished() {
    return m_iterator == m_text.end();
}

std::set<ITokenGenerator*> Lexer::prepareCandidates() const {
    auto candidates = std::set<ITokenGenerator*>();
    for (const auto& gen : m_tokenGens) {
        candidates.insert(gen.get());
    }
    return candidates;
}

Lexer& Lexer::addTokenGenerator(std::unique_ptr<ITokenGenerator> gen) {
    const ITokenGenerator& candidate = *gen;
    for (const auto& existing : m_tokenGens) {
        if (const ITokenGenerator& registered = *existing;
                typeid(registered) == typeid(candidate)) {
            return *this;  // a generator of this concrete type is already registered
        }
    }

    m_tokenGens.emplace(std::move(gen));
    return *this;
}

std::unique_ptr<Token> Lexer::lexToken() {
    if (isFinished()) {
        return nullptr;
    }

    skipFiller();

    auto candidates = prepareCandidates();
    bool validSeq;
    std::string payload;
    const ITokenGenerator* lastFailedGen = nullptr;

    do {
        validSeq = false;
        for (auto gen_itr = candidates.begin(); gen_itr != candidates.end() && !isFinished();) {
            const auto& gen = *gen_itr;

            if (gen->check(m_peek, payload)) {
                validSeq = true;
                advance(payload);

                if (isFinished()) {
                    lastFailedGen = *gen_itr;
                } else {
                    ++gen_itr;
                }
                continue;
            }

            lastFailedGen = *gen_itr;
            gen_itr = candidates.erase(gen_itr);
        }
    } while(validSeq && !isFinished());

    if (lastFailedGen == nullptr || payload.empty()) {
        throw std::logic_error("Lexer::addTokenGenerator: Unexpected token at line " + std::to_string(m_lineNumber));
    }
    return lastFailedGen->generate(payload);
}