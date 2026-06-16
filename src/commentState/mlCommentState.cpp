#include "mlCommentState.hpp"

std::unique_ptr<ICommentState> MLCommentState::update(const char peek) const {
    if (peek == '*') {
        return std::make_unique<EndMLCommentState>();
    }

    return nullptr;
}

bool MLCommentState::isSkippable() const {
    return true;
}