#include "initCommentState.hpp"

const InitCommentState& InitCommentState::getInstance() {
    static InitCommentState instance;
    return instance;
}

const ICommentState& InitCommentState::update(const char peek) const {
    if (peek == '/') {
        return LineCommentState::getInstance();
    }

    if (peek == '*') {
        return MLCommentState::getInstance();
    }

    return NoCommentState::getInstance();
}

bool InitCommentState::isSkippable() const {
    return false;
}

bool InitCommentState::mustCloseBeforeEnd() const {
    return false;
}