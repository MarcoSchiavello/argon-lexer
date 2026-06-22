#pragma once
#include "iCommentState.hpp"
#include "noCommentState.hpp"

class LineCommentState : public ICommentState {
    public:
        ~LineCommentState() override = default;
        LineCommentState(const LineCommentState&) = delete;
        LineCommentState& operator=(const LineCommentState&) = delete;

        [[nodiscard]] const ICommentState& update(char peek) const override;
        [[nodiscard]] bool isSkippable() const override;
        [[nodiscard]] bool mustCloseBeforeEnd() const override;
        static const LineCommentState& getInstance();

    private:
        LineCommentState() = default;
};
