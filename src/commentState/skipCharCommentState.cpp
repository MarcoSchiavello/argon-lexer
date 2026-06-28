#include "skipCharCommentState.hpp"

const SkipCharCommentState& SkipCharCommentState::getInstance() {
    static SkipCharCommentState instance;
    return instance;
}

const ICommentState& SkipCharCommentState::update(const char peek) const {
    return NoCommentState::getInstance().update(peek);
}

bool SkipCharCommentState::isSkippable() const {
    return true;
}

bool SkipCharCommentState::mustCloseBeforeEnd() const {
    return false;
}