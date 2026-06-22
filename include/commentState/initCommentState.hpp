#pragma once

#include "iCommentState.hpp"
#include "lineCommentState.hpp"
#include "mlCommentState.hpp"
#include "noCommentState.hpp"


class InitCommentState : public ICommentState {
    public:
        ~InitCommentState() override = default;
        InitCommentState(const InitCommentState&) = delete;
        InitCommentState& operator=(const InitCommentState&) = delete;

        [[nodiscard]] const ICommentState& update(char peek) const override;
        [[nodiscard]] bool isSkippable() const override;
        [[nodiscard]] bool mustCloseBeforeEnd() const override;
        static const InitCommentState& getInstance();

    private:
        InitCommentState() = default;
};
