//
//
//

#include <gtest/gtest.h>

#include "DateTime.h"

class DateTimeF : public testing::Test {
};

TEST_F(DateTimeF, tomorrow_greater_than_today)
{
    auto today = DateTime::Now();
    auto tomorrow = today.AddDays(1.0);

    ASSERT_TRUE(tomorrow >= today);
    ASSERT_FALSE(today >= tomorrow);
};

TEST_F(DateTimeF, today_equal_today)
{
    auto today = DateTime::Now();
    auto today_too = today.AddDays(0);

    ASSERT_TRUE(today_too >= today);
    ASSERT_TRUE(today >= today_too);
};


TEST_F(DateTimeF, epoch_time)
{
    DateTime actual{1970, 1, 1};
    DateTime actual2{1970, 1, 1};

    ASSERT_EQ(actual, actual2);
}