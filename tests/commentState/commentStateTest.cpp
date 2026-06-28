#include <gtest/gtest.h>

#include "iCommentState.hpp"
#include "noCommentState.hpp"
#include "initCommentState.hpp"
#include "lineCommentState.hpp"
#include "mlCommentState.hpp"
#include "endMlCommentState.hpp"
#include "skipCharCommentState.hpp"

namespace {

const ICommentState* ptr(const ICommentState& s) { return &s; }

}

TEST(CommentState, NoCommentStartsInitOnSlash) {
    const auto& s = NoCommentState::getInstance();
    EXPECT_EQ(ptr(s.update('/')), ptr(InitCommentState::getInstance()));
}

TEST(CommentState, NoCommentStaysOnOtherChars) {
    const auto& s = NoCommentState::getInstance();
    EXPECT_EQ(ptr(s.update('x')), ptr(s));
    EXPECT_EQ(ptr(s.update('*')), ptr(s));
    EXPECT_EQ(ptr(s.update('\n')), ptr(s));
}

TEST(CommentState, NoCommentFlags) {
    const auto& s = NoCommentState::getInstance();
    EXPECT_FALSE(s.isSkippable());
    EXPECT_FALSE(s.mustCloseBeforeEnd());
}

TEST(CommentState, InitToLineOnSecondSlash) {
    const auto& s = InitCommentState::getInstance();
    EXPECT_EQ(ptr(s.update('/')), ptr(LineCommentState::getInstance()));
}

TEST(CommentState, InitToMultilineOnStar) {
    const auto& s = InitCommentState::getInstance();
    EXPECT_EQ(ptr(s.update('*')), ptr(MLCommentState::getInstance()));
}

TEST(CommentState, InitBackToNoCommentOnOther) {
    const auto& s = InitCommentState::getInstance();
    EXPECT_EQ(ptr(s.update('x')), ptr(NoCommentState::getInstance()));
}

TEST(CommentState, InitFlags) {
    // A lone '/' is not yet a comment: not skippable, need not close.
    const auto& s = InitCommentState::getInstance();
    EXPECT_FALSE(s.isSkippable());
    EXPECT_FALSE(s.mustCloseBeforeEnd());
}

TEST(CommentState, LineEndsOnNewline) {
    const auto& s = LineCommentState::getInstance();
    EXPECT_EQ(ptr(s.update('\n')), ptr(NoCommentState::getInstance()));
}

TEST(CommentState, LineStaysOnOtherChars) {
    const auto& s = LineCommentState::getInstance();
    EXPECT_EQ(ptr(s.update('x')), ptr(s));
    EXPECT_EQ(ptr(s.update('/')), ptr(s));
    EXPECT_EQ(ptr(s.update('*')), ptr(s));
}

TEST(CommentState, LineFlags) {
    // Skippable, and may legally run to end-of-input (no closing token).
    const auto& s = LineCommentState::getInstance();
    EXPECT_TRUE(s.isSkippable());
    EXPECT_FALSE(s.mustCloseBeforeEnd());
}

TEST(CommentState, MultilineToEndOnStar) {
    const auto& s = MLCommentState::getInstance();
    EXPECT_EQ(ptr(s.update('*')), ptr(EndMLCommentState::getInstance()));
}

TEST(CommentState, MultilineStaysOnOtherChars) {
    const auto& s = MLCommentState::getInstance();
    EXPECT_EQ(ptr(s.update('x')), ptr(s));
    EXPECT_EQ(ptr(s.update('/')), ptr(s));
    EXPECT_EQ(ptr(s.update('\n')), ptr(s));
}

TEST(CommentState, MultilineFlags) {
    const auto& s = MLCommentState::getInstance();
    EXPECT_TRUE(s.isSkippable());
    EXPECT_TRUE(s.mustCloseBeforeEnd());
}

TEST(CommentState, EndMlToSkipCharOnSlash) {
    const auto& s = EndMLCommentState::getInstance();
    EXPECT_EQ(ptr(s.update('/')), ptr(SkipCharCommentState::getInstance()));
}

TEST(CommentState, EndMlStaysOnStar) {
    // A run of stars keeps us poised to close: "**/" must still terminate.
    const auto& s = EndMLCommentState::getInstance();
    EXPECT_EQ(ptr(s.update('*')), ptr(s));
}

TEST(CommentState, EndMlBackToMultilineOnOther) {
    const auto& s = EndMLCommentState::getInstance();
    EXPECT_EQ(ptr(s.update('x')), ptr(MLCommentState::getInstance()));
}

TEST(CommentState, EndMlFlags) {
    const auto& s = EndMLCommentState::getInstance();
    EXPECT_TRUE(s.isSkippable());
    EXPECT_TRUE(s.mustCloseBeforeEnd());
}

TEST(CommentState, SkipCharStartsNewCommentOnSlash) {
    // A '/' immediately after a block comment closes begins a fresh comment,
    // so "*//" and "*/ /*" chain correctly.
    const auto& s = SkipCharCommentState::getInstance();
    EXPECT_EQ(ptr(s.update('/')), ptr(InitCommentState::getInstance()));
}

TEST(CommentState, SkipCharReturnsToNoCommentOnOther) {
    const auto& s = SkipCharCommentState::getInstance();
    EXPECT_EQ(ptr(s.update('x')), ptr(NoCommentState::getInstance()));
    EXPECT_EQ(ptr(s.update('\n')), ptr(NoCommentState::getInstance()));
}

TEST(CommentState, SkipCharFlags) {
    // The closing '/' is consumed as part of the comment, so it is skippable,
    // but the comment is already complete, so it need not close again.
    const auto& s = SkipCharCommentState::getInstance();
    EXPECT_TRUE(s.isSkippable());
    EXPECT_FALSE(s.mustCloseBeforeEnd());
}