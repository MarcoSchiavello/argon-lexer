#pragma once
#include "iCommentState.hpp"
#include "noCommentState.hpp"

class EndMLCommentState : public ICommentState {
    public:
        ~EndMLCommentState() override = default;
        [[nodiscard]] std::unique_ptr<ICommentState> update(char peek) const override;
        [[nodiscard]] bool isSkippable() const override;
};
