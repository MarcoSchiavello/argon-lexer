#include "mlCommentState.hpp"

const MLCommentState& MLCommentState::getInstance() {
    static MLCommentState instance;
    return instance;
}

const ICommentState& MLCommentState::update(const char peek) const {
    if (peek == '*') {
        return EndMLCommentState::getInstance();
    }

    return *this;
}

bool MLCommentState::isSkippable() const {
    return true;
}

bool MLCommentState::mustCloseBeforeEnd() const {
    return true;
}