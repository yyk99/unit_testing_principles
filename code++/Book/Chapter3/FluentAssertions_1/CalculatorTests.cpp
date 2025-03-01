#include <gtest/gtest.h>

// using FluentAssertions;
// using Xunit;

class Calculator
{
public:
    double Sum(double first, double second)
    {
        return first + second;
    }
};

class CalculatorTests : public testing::Test
{
};

// [Fact]
TEST_F(CalculatorTests,Sum_of_two_numbers)
{
    double first = 10;
    double second = 20;
    Calculator sut{};

    double result = sut.Sum(first,second);

    ASSERT_DOUBLE_EQ(30, result);
}

