#pragma once
#include <memory>

class ICommentState {
    public:
        virtual ~ICommentState() = default;
        [[nodiscard]] virtual std::unique_ptr<ICommentState> update(char peek) const = 0;
        [[nodiscard]] virtual bool isSkippable() const = 0;
        [[nodiscard]] virtual bool mustCloseBeforeEnd() const = 0;
};
