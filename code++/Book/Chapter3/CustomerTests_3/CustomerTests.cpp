
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// Book/Chapter3/CustomerTests_3/CustomerTests.cpp
// Book/Chapter2/Listing1/Other.h

#include "../../Chapter2/Listing1/Other.h"

using namespace book::chapter2::listing1;
// using Xunit;

namespace Book::Chapter3::CustomerTests_3
{
#if 0
}
#endif

class CustomerTests: public testing::Test
{
protected:
    Store _store;
    Customer _sut;

public:
    CustomerTests()
    {
        _store.AddInventory(Product::Shampoo,10);
    }
};

// [Fact]
TEST_F(CustomerTests,Purchase_succeeds_when_enough_inventory)
{
    bool success = _sut.Purchase(_store,Product::Shampoo,5);

    ASSERT_TRUE(success);
    ASSERT_EQ(5,_store.GetInventory(Product::Shampoo));
}

// [Fact]
TEST_F(CustomerTests,Purchase_fails_when_not_enough_inventory)
{
    bool success = _sut.Purchase(_store,Product::Shampoo,15);

    ASSERT_FALSE(success);
    ASSERT_EQ(10,_store.GetInventory(Product::Shampoo));
}

} // namespaces