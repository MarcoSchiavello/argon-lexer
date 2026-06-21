#include "lineCommentState.hpp"

std::unique_ptr<ICommentState> LineCommentState::update(const char peek) const {
    if (peek == '\n') {
        return std::make_unique<NoCommentState>();
    }

    return nullptr;
}


bool LineCommentState::isSkippable() const {
    return true;
}

bool LineCommentState::mustCloseBeforeEnd() const {
    return false;
}