#include "initCommentState.hpp"

std::unique_ptr<ICommentState> InitCommentState::update(const char peek) const {
    if (peek == '/') {
        return std::make_unique<LineCommentState>();
    }

    if (peek == '*') {
        return std::make_unique<MLCommentState>();
    }

    return std::make_unique<NoCommentState>();
}

bool InitCommentState::isSkippable() const {
    return false;
}

bool InitCommentState::mustCloseBeforeEnd() const {
    return false;
}