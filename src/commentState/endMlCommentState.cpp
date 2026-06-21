#include "endMlCommentState.hpp"

std::unique_ptr<ICommentState> EndMLCommentState::update(const char peek) const {
    if (peek == '/') {
        return std::make_unique<NoCommentState>();
    }

    return std::make_unique<MLCommentState>();
}

bool EndMLCommentState::isSkippable() const {
    return true;
}

bool EndMLCommentState::mustCloseBeforeEnd() const {
    return true;
}