#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Other.h"

using namespace book::chapter2::listing2;

class IStoreMock : public IStore
{
public:
    MOCK_METHOD(bool, HasEnoughInventory, (Product product, int quantity), (override));
    MOCK_METHOD(void, RemoveInventory, (Product product, int quantity), (override));
    MOCK_METHOD(void, AddInventory, (Product product, int quantity), (override));
    MOCK_METHOD(int, GetInventory, (Product product), (override));
};

class CustomerTests2 : public testing::Test
{
};

#if 1

//[Fact]
TEST_F(CustomerTests2, Purchase_succeeds_when_enough_inventory)
{
    using ::testing::Return;
    using ::testing::AtLeast;

    // Arrange
    IStoreMock storeMock; // = new Mock<IStore>();
    // storeMock
    //     .Setup(x = > x.HasEnoughInventory(Product.Shampoo, 5))
    //     .Returns(true);
    EXPECT_CALL(storeMock, HasEnoughInventory(Product::Shampoo, 5))
        .Times(1)
        .WillRepeatedly(Return(true));
    EXPECT_CALL(storeMock, RemoveInventory(Product::Shampoo, 5))
        .Times(1);

    Customer customer;

    // Act
    bool success = customer.Purchase(storeMock, Product::Shampoo, 5);

    // Assert
    ASSERT_TRUE(success);
    // storeMock.Verify(x = > x.RemoveInventory(Product.Shampoo, 5), Times.Once);
}

//[Fact]
TEST_F(CustomerTests2, Purchase_fails_when_not_enough_inventory)
{
    using ::testing::Return;
    // Arrange
    IStoreMock storeMock;
    // storeMock
    //     .Setup(x = > x.HasEnoughInventory(Product.Shampoo, 5))
    //     .Returns(false);
    EXPECT_CALL(storeMock, HasEnoughInventory(Product::Shampoo, 5))
        .WillRepeatedly(Return(false));

    Customer customer;

    // Act
    bool success = customer.Purchase(storeMock, Product::Shampoo, 5);

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
    using ::testing::AtLeast;
    using ::testing::Return;

    MockTurtle turtle;
    EXPECT_CALL(turtle, PenDown()).Times(AtLeast(1));
    EXPECT_CALL(turtle, GoTo(0,0)).Times(1);

    Painter painter(&turtle);

    EXPECT_TRUE(painter.DrawCircle(0, 0, 10));
}

#endif
