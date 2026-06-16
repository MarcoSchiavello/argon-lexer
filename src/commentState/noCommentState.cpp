#include "noCommentState.hpp"

std::unique_ptr<ICommentState> NoCommentState::update(const char peek) const {
    if (peek == '/') {
        return std::make_unique<InitCommentState>();
    }

    return nullptr;
}

bool NoCommentState::isSkippable() const {
    return false;
}