#pragma once

#include "iCommentState.hpp"
#include "initCommentState.hpp"

class NoCommentState : public ICommentState {
    public:
        ~NoCommentState() override = default;
        NoCommentState(const NoCommentState&) = delete;
        NoCommentState& operator=(const NoCommentState&) = delete;

        [[nodiscard]] const ICommentState& update(char peek) const override;
        [[nodiscard]] bool isSkippable() const override;
        [[nodiscard]] bool mustCloseBeforeEnd() const override;
        static const NoCommentState& getInstance();

    private:
        NoCommentState() = default;
};
