#pragma once

#include "iCommentState.hpp"
#include "lineCommentState.hpp"
#include "mlCommentState.hpp"
#include "noCommentState.hpp"


class InitCommentState : public ICommentState {
    public:
        ~InitCommentState() override = default;
        [[nodiscard]] std::unique_ptr<ICommentState> update(char peek) const override;
        [[nodiscard]] bool isSkippable() const override;
        [[nodiscard]] bool mustCloseBeforeEnd() const override;
};
