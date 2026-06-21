#include "lexer.hpp"

#include <typeinfo>

Lexer::Lexer(const std::string& text) {
    m_lineNumber = 0;
    m_text = text;
    m_iterator = m_text.begin();
    m_peek = *m_iterator;
    m_commentState = std::make_unique<NoCommentState>();
}

void Lexer::skipFiller() {
    while  (m_peek == ' ' || m_peek == '\n' || m_commentState->isSkippable()) {
        if (isFinished()) {
            if (m_closeToken )
            return;
        }

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
    m_iteratorLookAhead++;
    m_peek = *(m_iterator+m_iteratorLookAhead);

    if (auto newState = m_commentState->update(m_peek)) {
        m_commentState = std::move(newState);
    }

    m_closeToken = m_commentState->isSkippable();
}

void Lexer::commit() {
    m_iterator += m_iteratorLookAhead;
    m_iteratorLookAhead = 0;
}

bool Lexer::isFinished() {
    return m_iterator+m_iteratorLookAhead == m_text.end();
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
    m_iteratorLookAhead = 0;
    skipFiller();

    if (isFinished()) {
        if (m_commentState->mustCloseBeforeEnd()) {
            throw std::logic_error("Lexer::addTokenGenerator: Illegal comment state on document's end");
        }
        return nullptr;
    }

    auto candidates = prepareCandidates();
    bool validSeq;
    std::string payload;
    struct {
        ITokenGenerator* gen;
        size_t len;
    } lastAccepted = { nullptr, 0 };

    do {
        validSeq = false;
        for (auto gen_itr = candidates.begin(); gen_itr != candidates.end();) {
            const auto& gen = *gen_itr;

            if (gen->check(m_peek, payload)) {
                validSeq = true;
                ++gen_itr;
                continue;
            }

            if (gen->accept(payload)) {
                lastAccepted.gen = gen;
                lastAccepted.len = payload.length();
                commit();
            }

            gen_itr = candidates.erase(gen_itr);
        }

        if (validSeq) {
            advance(payload);
        }
    } while(validSeq && !m_closeToken);

    if (m_commentState->isSkippable() && payload=="/") {
        return lexToken();
    }

    if (lastAccepted.gen == nullptr) {
        throw std::logic_error("Lexer::addTokenGenerator: Unexpected token '"+payload+"' at line " + std::to_string(m_lineNumber));
    }
    return lastAccepted.gen->generate(payload.substr(0, lastAccepted.len));
}