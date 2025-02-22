#include "gtest/gtest.h"

#include "Other.h"

using namespace book::chapter2::listing1;
  
class CustomerTests : public testing::Test
{

};

TEST_F(CustomerTests, Purchase_succeeds_when_enough_inventory)
{
    // Arrange
    Store store;
    store.AddInventory(Product::Shampoo, 10);
    Customer customer;

    // Act
    bool success = customer.Purchase(store, Product::Shampoo, 5);

    // Assert
    ASSERT_TRUE(success);
    ASSERT_EQ(5, store.GetInventory(Product::Shampoo));
}

TEST_F(CustomerTests, Purchase_fails_when_not_enough_inventory)
{
    // Arrange
    Store store;
    store.AddInventory(Product::Shampoo, 10);
    Customer customer;

    // Act
    bool success = customer.Purchase(store, Product::Shampoo, 15);

    // Assert
    ASSERT_TRUE(success);
    ASSERT_EQ(10, store.GetInventory(Product::Shampoo));
}
