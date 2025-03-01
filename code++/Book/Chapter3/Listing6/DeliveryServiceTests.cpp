#include <gtest/gtest.h>

#include "DebuggingConsole.h"

class DateTime
{
    time_t m_current_time;
public:
    DateTime() 
    {
        time(&m_current_time);
    }

    static DateTime Now() { return DateTime{}; }

    DateTime AddDays(double d) const
    {
        DateTime r = *this;

        r.m_current_time += (time_t)(d * 24 * 3600);
        return r;
    }

    bool operator>=(DateTime const &right) const
    {
        return m_current_time >= right.m_current_time;
    }
};


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

class Delivery
{
public:
    DateTime Date;
};

class DeliveryService
{
public:
    bool IsDeliveryValid(Delivery delivery)
    {
        return delivery.Date >= DateTime::Now().AddDays(1.999);
    }
};

typedef std::pair<int, bool> IntBool;

class DeliveryServiceTestsIntBool : public testing::TestWithParam<IntBool> 
{
};


TEST_P(DeliveryServiceTestsIntBool, Detects_an_invalid_delivery_date)
{
    int daysFromNow = GetParam().first; 
    bool expected = GetParam().second;

    CONSOLE("Detects_an_invalid_delivery_date: " << daylight << ", " << expected);

    {
        DeliveryService sut;
        DateTime deliveryDate = DateTime::Now().AddDays(daysFromNow);
        Delivery delivery;
        delivery.Date = deliveryDate;

        bool isValid = sut.IsDeliveryValid(delivery);

        ASSERT_EQ(expected, isValid);
    }
};
// [InlineData(-1, false)]
// [InlineData(0, false)]
// [InlineData(1, false)]
// [InlineData(2, true)]
// [Theory]

INSTANTIATE_TEST_SUITE_P(Group_IntBool,
    DeliveryServiceTestsIntBool,
    testing::Values(
        IntBool(-1, false),
        IntBool(0, false),
        IntBool(1, false),
        IntBool(2, true)
    )
);


#if 0
    // [InlineData(-1)]
    // [InlineData(0)]
    // [InlineData(1)]
    // [Theory] 
    void
        Detects_an_invalid_delivery_date2(int daysFromNow)
    {
        DeliveryService sut = new DeliveryService();
        DateTime deliveryDate = DateTime.Now.AddDays(daysFromNow);
        Delivery delivery = new Delivery{
            Date = deliveryDate};

        bool isValid = sut.IsDeliveryValid(delivery);

        Assert.False(isValid);
    }
}

//[Fact]
void The_soonest_delivery_date_is_two_days_from_now()
{
    DeliveryService sut = new DeliveryService();
    DateTime deliveryDate = DateTime.Now.AddDays(2);
    Delivery delivery = new Delivery{
        Date = deliveryDate};

    bool isValid = sut.IsDeliveryValid(delivery);

    Assert.True(isValid);
}

// [Theory]
// [MemberData(nameof(Data))]
void Detects_an_invalid_delivery_date3(
        DateTime deliveryDate,
        bool expected)
{
    DeliveryService sut = new DeliveryService();
    Delivery delivery = new Delivery{
        Date = deliveryDate};

    bool isValid = sut.IsDeliveryValid(delivery);

    Assert.Equal(expected, isValid);
}

static List<object[]> Data()
{
    return new List<object[]>{
        new object[]{DateTime.Now.AddDays(-1), false},
        new object[]{DateTime.Now, false},
        new object[]{DateTime.Now.AddDays(1), false},
        new object[]{DateTime.Now.AddDays(2), true}};
}

#endif
