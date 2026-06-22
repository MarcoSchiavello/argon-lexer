#include "endMlCommentState.hpp"
#include "mlCommentState.hpp"


const EndMLCommentState& EndMLCommentState::getInstance() {
    static EndMLCommentState instance;
    return instance;
}

const ICommentState& EndMLCommentState::update(const char peek) const {
    if (peek == '/') {
        return NoCommentState::getInstance();
    }

    if (peek == '*') {
        return *this;
    }

    return MLCommentState::getInstance();
}

bool EndMLCommentState::isSkippable() const {
    return true;
}

bool EndMLCommentState::mustCloseBeforeEnd() const {
    return true;
}

