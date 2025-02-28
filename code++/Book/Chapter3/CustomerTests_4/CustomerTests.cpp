#include <gmock/gmock.h>
#include <gtest/gtest.h>

// using System;
// using Book.Chapter2.Listing1;
// using Xunit;

#include "../../Chapter2/Listing1/Other.h"

using namespace book::chapter2::listing1;

class CustomerTests_4: public testing::Test
{
protected:
    Store CreateStoreWithInventory(Product product,int quantity)
    {
        Store store;
        store.AddInventory(product,quantity);
        return store;
    }

    static Customer CreateCustomer()
    {
        return Customer{};
    }
};

// [Fact]
TEST_F(CustomerTests_4,Purchase_succeeds_when_enough_inventory)
{
    Store store = CreateStoreWithInventory(Product::Shampoo,10);
    Customer sut = CreateCustomer();

    bool success = sut.Purchase(store,Product::Shampoo,5);

    ASSERT_TRUE(success);
    ASSERT_EQ(5,store.GetInventory(Product::Shampoo));
};

// [Fact]
TEST_F(CustomerTests_4,Purchase_fails_when_not_enough_inventory)
{
    Store store = CreateStoreWithInventory(Product::Shampoo,10);
    Customer sut = CreateCustomer();

    bool success = sut.Purchase(store,Product::Shampoo,15);

    ASSERT_FALSE(success);
    ASSERT_EQ(10,store.GetInventory(Product::Shampoo));
}

class Database
{
public:
    virtual ~Database() {std::cout << "~Database()\n";}
};

class IntegrationTests: public testing::Test
{
protected:
    Database _database;

    IntegrationTests()
    {
    }

    virtual ~IntegrationTests()
    {
        std::cout << "~IntegrationTests()\n";
    }
};

class CustomerTests42: public IntegrationTests
{};

// [Fact]
TEST_F(CustomerTests42,Purchase_succeeds_when_enough_inventory)
{
    /* ... */
    ;
};
