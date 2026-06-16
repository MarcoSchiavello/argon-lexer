#pragma once
#include "iCommentState.hpp"
#include "endMlCommentState.hpp"

class MLCommentState : public ICommentState {
    public:
        ~MLCommentState() override = default;
        [[nodiscard]] std::unique_ptr<ICommentState> update(char peek) const override;
        [[nodiscard]] bool isSkippable() const override;
};
