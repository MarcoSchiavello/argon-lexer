#include <stdexcept>

#include <gtest/gtest.h>

#include "lexerTestUtils.hpp"

using argon::test::lexAll;
using argon::test::lexJoined;
using argon::test::INT;
using argon::test::PLUS;
using argon::test::SLASH;

TEST(CommentRecognition, LineCommentBetweenTokens) {
    EXPECT_EQ(lexJoined("2 // adds nothing\n+ 3"), INT(2) + " " + PLUS + " " + INT(3));
}

TEST(CommentRecognition, LineCommentAtEndOfInputWithoutNewline) {
    EXPECT_EQ(lexJoined("2 // trailing"), INT(2));
}

TEST(CommentRecognition, LeadingLineComment) {
    EXPECT_EQ(lexJoined("// header\n42"), INT(42));
}

TEST(CommentRecognition, OnlyALineCommentYieldsNoTokens) {
    EXPECT_EQ(lexJoined("// just a comment"), "");
}

TEST(CommentRecognition, LineCommentDoesNotSwallowNextLine) {
    EXPECT_EQ(lexJoined("1 // a\n2 // b\n3"), INT(1) + " " + INT(2) + " " + INT(3));
}

TEST(CommentRecognition, BlockCommentBetweenTokens) {
    EXPECT_EQ(lexJoined("2/* x */+3"), INT(2) + " " + PLUS + " " + INT(3));
}

TEST(CommentRecognition, LeadingBlockComment) {
    EXPECT_EQ(lexJoined("/* x */2"), INT(2));
}

TEST(CommentRecognition, EmptyBlockComment) {
    EXPECT_EQ(lexJoined("/**/2"), INT(2));
}

TEST(CommentRecognition, OnlyABlockCommentYieldsNoTokens) {
    EXPECT_EQ(lexJoined("/* nothing */"), "");
}

TEST(CommentRecognition, BlockCommentSpanningLines) {
    EXPECT_EQ(lexJoined("1/* line one\n line two */2"), INT(1) + " " + INT(2));
}

TEST(CommentRecognition, BlockCommentWithLeadingDoubleStar) {
    EXPECT_EQ(lexJoined("/** doc */2"), INT(2));
}

TEST(CommentRecognition, BlockCommentClosingWithDoubleStar) {
    EXPECT_EQ(lexJoined("/* x **/2"), INT(2));
}

TEST(CommentRecognition, BlockCommentWithInteriorLoneStar) {
    EXPECT_EQ(lexJoined("/* a * b */2"), INT(2));
}

TEST(CommentRecognition, BlockCommentWithRunOfStars) {
    EXPECT_EQ(lexJoined("/* a ***** b */2"), INT(2));
}

TEST(CommentRecognition, DivisionIsNotAComment) {
    EXPECT_EQ(lexJoined("4/2"), INT(4) + " " + SLASH + " " + INT(2));
}

TEST(CommentRecognition, DivisionFollowedByALineComment) {
    EXPECT_EQ(lexJoined("6/2 // q\n"), INT(6) + " " + SLASH + " " + INT(2));
}

TEST(CommentRecognition, BlockCommentContainingASlash) {
    EXPECT_EQ(lexJoined("/* a/b/c */7"), INT(7));
}

TEST(CommentRecognition, BlockCommentImmediatelyFollowedByLineComment) {
    EXPECT_EQ(lexJoined("/* a */// b\n2"), INT(2));
}

TEST(CommentRecognition, TwoBlockCommentsInARow) {
    EXPECT_EQ(lexJoined("/*a*//*b*/2"), INT(2));
}

TEST(CommentRecognition, UnterminatedBlockCommentThrows) {
    EXPECT_THROW(lexAll("/* never closed"), std::logic_error);
}

TEST(CommentRecognition, UnterminatedBlockCommentEndingOnStarThrows) {
    EXPECT_THROW(lexAll("/* x *"), std::logic_error);
}

TEST(CommentRecognition, UnterminatedEmptyBlockCommentThrows) {
    EXPECT_THROW(lexAll("/*"), std::logic_error);
}
