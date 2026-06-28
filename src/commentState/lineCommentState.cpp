#include "lineCommentState.hpp"

const LineCommentState& LineCommentState::getInstance() {
    static LineCommentState instance;
    return instance;
}

const ICommentState& LineCommentState::update(const char peek) const {
    if (peek == '\n') {
        return NoCommentState::getInstance();
    }

    return *this;
}


bool LineCommentState::isSkippable() const {
    return true;
}

bool LineCommentState::mustCloseBeforeEnd() const {
    return false;
}