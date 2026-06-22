#include "noCommentState.hpp"

const NoCommentState& NoCommentState::getInstance() {
    static NoCommentState instance;
    return instance;
}

const ICommentState& NoCommentState::update(const char peek) const {
    if (peek == '/') {
        return InitCommentState::getInstance();
    }

    return *this;
}

bool NoCommentState::isSkippable() const {
    return false;
}

bool NoCommentState::mustCloseBeforeEnd() const {
    return false;
}