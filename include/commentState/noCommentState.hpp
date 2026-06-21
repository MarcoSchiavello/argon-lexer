#pragma once

#include "iCommentState.hpp"
#include "initCommentState.hpp"

class NoCommentState : public ICommentState {
    public:
        ~NoCommentState() override = default;
        [[nodiscard]] std::unique_ptr<ICommentState> update(char peek) const override;
        [[nodiscard]] bool isSkippable() const override;
        [[nodiscard]] bool mustCloseBeforeEnd() const override;
};
