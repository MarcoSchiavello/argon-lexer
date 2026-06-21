#pragma once
#include "iCommentState.hpp"
#include "noCommentState.hpp"

class LineCommentState : public ICommentState {
    public:
        ~LineCommentState() override = default;
        [[nodiscard]] std::unique_ptr<ICommentState> update(char peek) const override;
        [[nodiscard]] bool isSkippable() const override;
        [[nodiscard]] bool mustCloseBeforeEnd() const override;
};
