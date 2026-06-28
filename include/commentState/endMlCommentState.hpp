#pragma once
#include "iCommentState.hpp"
#include "noCommentState.hpp"

class EndMLCommentState : public ICommentState {
    public:
        ~EndMLCommentState() override = default;
        EndMLCommentState(const EndMLCommentState&) = delete;
        EndMLCommentState& operator=(const EndMLCommentState&) = delete;

        [[nodiscard]] const ICommentState& update(char peek) const override;
        [[nodiscard]] bool isSkippable() const override;
        [[nodiscard]] bool mustCloseBeforeEnd() const override;
        static const EndMLCommentState& getInstance();

    private:
        EndMLCommentState() = default;
};
