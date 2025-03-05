#include <gtest/gtest.h>

#include "string_split.h"
#include "string_trim.h"

class StringTestF : public testing::Test {
};

TEST_F(StringTestF, split_empty)
{
    auto actual = split_string("", '@');
    ASSERT_EQ(0, actual.size());
}

TEST_F(StringTestF, split_regular)
{
    auto actual = split_string("foo@example.com", '@');
    ASSERT_EQ(2, actual.size());
}