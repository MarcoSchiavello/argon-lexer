#pragma once
#include "iCommentState.hpp"
#include "endMlCommentState.hpp"

class SkipCharCommentState : public ICommentState {
    public:
        ~SkipCharCommentState() override = default;
        SkipCharCommentState(const SkipCharCommentState&) = delete;
        SkipCharCommentState& operator=(const SkipCharCommentState&) = delete;

        [[nodiscard]] const ICommentState& update(char peek) const override;
        [[nodiscard]] bool isSkippable() const override;
        [[nodiscard]] bool mustCloseBeforeEnd() const override;
        static const SkipCharCommentState& getInstance();

    private:
        SkipCharCommentState() = default;
};
