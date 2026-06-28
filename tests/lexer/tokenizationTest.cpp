#include <gtest/gtest.h>

#include "lexerTestUtils.hpp"

using argon::test::lexJoined;
using argon::test::INT;
using argon::test::PLUS;
using argon::test::SLASH;

TEST(Tokenization, SingleNumber) {
    EXPECT_EQ(lexJoined("2"), INT(2));
}

TEST(Tokenization, MultiDigitNumber) {
    EXPECT_EQ(lexJoined("12345"), INT(12345));
}

TEST(Tokenization, Addition) {
    EXPECT_EQ(lexJoined("2+3"), INT(2) + " " + PLUS + " " + INT(3));
}

TEST(Tokenization, Division) {
    EXPECT_EQ(lexJoined("8/4"), INT(8) + " " + SLASH + " " + INT(4));
}

TEST(Tokenization, SpacesAreSkipped) {
    EXPECT_EQ(lexJoined("   7   "), INT(7));
}

TEST(Tokenization, NewlinesAreSkipped) {
    EXPECT_EQ(lexJoined("1\n+\n2"), INT(1) + " " + PLUS + " " + INT(2));
}

TEST(Tokenization, MixedExpression) {
    EXPECT_EQ(lexJoined("10 + 20 / 5"),
              INT(10) + " " + PLUS + " " + INT(20) + " " + SLASH + " " + INT(5));
}

TEST(Tokenization, EmptyInputYieldsNoTokens) {
    EXPECT_EQ(lexJoined(""), "");
}

TEST(Tokenization, WhitespaceOnlyYieldsNoTokens) {
    EXPECT_EQ(lexJoined("   \n  \n"), "");
}