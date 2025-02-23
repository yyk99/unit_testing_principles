#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Other.h"

using namespace book::chapter2::listing2;

class CustomerTests : public testing::Test
{
};

#if 0

//[Fact]
TEST_F(CustomerTests, Purchase_succeeds_when_enough_inventory)
{
    // Arrange
    // auto storeMock = new Mock<IStore>();
    // storeMock
    //     .Setup(x = > x.HasEnoughInventory(Product.Shampoo, 5))
    //     .Returns(true);
    auto customer = new Customer();

    // Act
    bool success = customer->Purchase(storeMock.Object, Product::Shampoo, 5);

    // Assert
    ASSERT_TRUE(success);
    // storeMock.Verify(x = > x.RemoveInventory(Product.Shampoo, 5), Times.Once);
}

//[Fact]
TEST_F(CustomerTests, Purchase_fails_when_not_enough_inventory)
{
    // Arrange
    auto storeMock = new Mock<IStore>();
    storeMock
        .Setup(x = > x.HasEnoughInventory(Product.Shampoo, 5))
        .Returns(false);
    auto customer = new Customer();

    // Act
    bool success = customer->Purchase(storeMock.Object, Product::Shampoo, 5);

    // Assert
    ASSERT_FALSE(success);
    //storeMock.Verify(x = > x.RemoveInventory(Product.Shampoo, 5), Times.Never);
}

#endif

#if 1
//
// gmock for dummies
//

class Turtle
{
public:
    virtual ~Turtle() {}
    virtual void PenUp() = 0;
    virtual void PenDown() = 0;
    virtual void Forward(int distance) = 0;
    virtual void Turn(int degrees) = 0;
    virtual void GoTo(int x, int y) = 0;
    virtual int GetX() const = 0;
    virtual int GetY() const = 0;
};


class MockTurtle : public Turtle {
public:
    MOCK_METHOD(void, PenUp, (), (override));
    MOCK_METHOD(void, PenDown, (), (override));
    MOCK_METHOD(void, Forward, (int distance), (override));
    MOCK_METHOD(void, Turn, (int degrees), (override));
    MOCK_METHOD(void, GoTo, (int x, int y), (override));
    MOCK_METHOD(int, GetX, (), (const, override));
    MOCK_METHOD(int, GetY, (), (const, override));
};

using ::testing::AtLeast;                         // #1

class Painter {
public:
    Painter(Turtle *api)
    : m_api(api)
    {

    }

    bool DrawCircle(int x, int y, int r)
    {
        m_api->GoTo(x, y);
        m_api->PenDown();

        return true;
    }
protected:
    Turtle *m_api;
};


TEST(PainterTest, CanDrawSomething)
{
    MockTurtle turtle;
    EXPECT_CALL(turtle, PenDown()).Times(AtLeast(1));

    Painter painter(&turtle);

    EXPECT_TRUE(painter.DrawCircle(0, 0, 10));
}

#endif
