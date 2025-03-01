//
//
//

#include <gtest/gtest.h>

class Calculator
{
public:
    double Sum(double first,double second)
    {
        return first + second;
    }

    void CleanUp()
    {}
};

class CalculatorTests: public testing::Test
{};

// [Fact]
TEST_F(CalculatorTests,Sum_of_two_numbers)
{
    // Arrange
    double first = 10;
    double second = 20;
    Calculator calculator ;

    // Act
    double result = calculator.Sum(first,second);

    // Assert
    ASSERT_EQ(30,result);
};


class CalculatorTests2: public testing::Test
{
protected:
    Calculator _calculator;
public:
    CalculatorTests2()
    {}

    ~CalculatorTests2()
    {
        _calculator.CleanUp();
    }
};

// [Fact]
TEST_F(CalculatorTests2,Sum_of_two_numbers)
{
    // Arrange
    double first = 10;
    double second = 20;

    // Act
    double result = _calculator.Sum(first,second);

    // Assert
    ASSERT_EQ(30,result);
};

