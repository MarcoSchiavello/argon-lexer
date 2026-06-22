#pragma once
#include "iCommentState.hpp"
#include "endMlCommentState.hpp"

class MLCommentState : public ICommentState {
    public:
        ~MLCommentState() override = default;
        MLCommentState(const MLCommentState&) = delete;
        MLCommentState& operator=(const MLCommentState&) = delete;

        [[nodiscard]] const ICommentState& update(char peek) const override;
        [[nodiscard]] bool isSkippable() const override;
        [[nodiscard]] bool mustCloseBeforeEnd() const override;
        static const MLCommentState& getInstance();

    private:
        MLCommentState() = default;
};
