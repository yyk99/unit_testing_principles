#include "gtest/gtest.h"

#include "Other.h"

namespace Book::Chapter2::Listing1
{
#if 0
}
#endif
  
class CustomerTests : public testing::Test
{

};

TEST_F(CustomerTests, Purchase_succeeds_when_enough_inventory)
{
    // Arrange
    var store = new Store();
    store.AddInventory(Product.Shampoo, 10);
    var customer = new Customer();

    // Act
    bool success = customer.Purchase(store, Product.Shampoo, 5);

    // Assert
    Assert.True(success);
    Assert.Equal(5, store.GetInventory(Product.Shampoo));
}

TEST_F(CustomerTests, Purchase_fails_when_not_enough_inventory)
{
    // Arrange
    var store = new Store();
    store.AddInventory(Product.Shampoo, 10);
    var customer = new Customer();

    // Act
    bool success = customer.Purchase(store, Product.Shampoo, 15);

    // Assert
    Assert.False(success);
    Assert.Equal(10, store.GetInventory(Product.Shampoo));
}
} // namespace
