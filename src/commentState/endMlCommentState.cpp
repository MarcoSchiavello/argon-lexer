#include "endMlCommentState.hpp"

std::unique_ptr<ICommentState> EndMLCommentState::update(const char peek) const {
    if (peek == '/') {
        return std::make_unique<NoCommentState>();
    }

    return nullptr;
}

bool EndMLCommentState::isSkippable() const {
    return true;
}