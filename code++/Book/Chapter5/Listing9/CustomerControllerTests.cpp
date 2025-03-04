//
//
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class IEmailGateway
{
public:
    virtual void SendReceipt(
        std::string email, 
        std::string productName, 
        int quantity) = 0;
    virtual ~IEmailGateway() {}
};

class EmailGateway : public IEmailGateway
{
public:
    void SendReceipt(std::string email, std::string productName, int quantity) override
    {
    }
};

class Product
{
public:
    int Id;
    std::string Name;
    static Product Shampoo;
};

Product Product::Shampoo;

bool operator < (Product const& l, Product const& r)
{
    return l.Id < r.Id;
};

bool operator == (Product const& l, Product const& r)
{
    return l.Id == r.Id;
};

class ProductRepository
{
public:
    Product GetById(int productId)
    {
        return Product();
    }
};

class IStore
{
public:
    virtual bool HasEnoughInventory(Product product, int quantity) = 0;
    virtual void RemoveInventory(Product product, int quantity) = 0;
    virtual void AddInventory(Product product, int quantity) = 0;
    virtual int GetInventory(Product product) = 0;

    virtual ~IStore() {};
};

class Customer
{
public:
    bool Purchase(IStore &store, Product product, int quantity)
    {
        if (!store.HasEnoughInventory(product, quantity))
        {
            return false;
        }

        store.RemoveInventory(product, quantity);

        return true;
    }

    std::string Email;
};

class CustomerRepository
{
public:
    Customer GetById(int customerId)
    {
        return Customer();
    }
};


class Store : public IStore
{
private:
    std::map<Product, int> _inventory;

public: 
    int Id;

    bool HasEnoughInventory(Product product, int quantity)
    {
        return GetInventory(product) >= quantity;
    }

    void RemoveInventory(Product product, int quantity)
    {
        if (!HasEnoughInventory(product, quantity))
        {
            throw std::runtime_error("Not enough inventory");
        }

        _inventory[product] -= quantity;
    }

    void AddInventory(Product product, int quantity)
    {
        if (_inventory.count(product))
        {
            _inventory[product] += quantity;
        }
        else
        {
            _inventory.insert({product, quantity});
        }
    }

    int GetInventory(Product product)
    {
        // bool productExists = _inventory.TryGetValue(product, out int remaining);
        // return productExists ? remaining : 0;
        auto pos = _inventory.find(product);
        return (pos != _inventory.end()) ? pos->second : 0;
    }
};

class Mock_IEmailGateway : public IEmailGateway
{
    // MOCK_METHOD(ReturnType, MethodName, (Args...), (Specs...));
    // void SendReceipt(std::string email, std::string productName, int quantity) override
    MOCK_METHOD(void, SendReceipt, (std::string, std::string, int ), (override));

};

class CustomerController
{
private:
    CustomerRepository _customerRepository;
    ProductRepository _productRepository;
    Store _mainStore;
    IEmailGateway &_emailGateway;

public:
    CustomerController(IEmailGateway& emailGateway)
        : _emailGateway(emailGateway)
    {
    }

    bool Purchase(int customerId, int productId, int quantity)
    {
        Customer customer = _customerRepository.GetById(customerId);
        Product product = _productRepository.GetById(productId);

        bool isSuccess = customer.Purchase(_mainStore, product, quantity);

        if (isSuccess)
        {
            _emailGateway.SendReceipt(customer.Email, product.Name, quantity);
        }

        return isSuccess;
    }
};


class CustomerControllerTests : public testing::Test
{
};

// [Fact(Skip = "Concept illustration only")]
TEST_F(CustomerControllerTests, Successful_purchase)
{
    GTEST_SKIP() << "Concept illustration only";

    auto mock = Mock_IEmailGateway();
    auto sut = CustomerController(mock);

    bool isSuccess = sut.Purchase(
        /*customerId:*/ 1, /*productId:*/ 2, /*quantity:*/ 5
    );

    ASSERT_TRUE(isSuccess);
    // mock.Verify(
    //     x => x.SendReceipt(
    //         "customer@email.com", "Shampoo", 5),
    //     Times.Once);
};
    
class Mock_IStore : public IStore
{
    public:
    MOCK_METHOD(bool, HasEnoughInventory, (Product, int), (override));
    MOCK_METHOD(void, RemoveInventory, (Product, int), (override));
    MOCK_METHOD(void, AddInventory, (Product, int), (override));
    MOCK_METHOD(int, GetInventory, (Product), (override));

};

class CustomerTests : public testing::Test
{
};

// [Fact]
TEST_F(CustomerTests, Purchase_succeeds_when_enough_inventory)
{
    using ::testing::Return;
    using ::testing::AtLeast;

    auto storeMock = Mock_IStore{};
    // storeMock
    //     .Setup(x = > x.HasEnoughInventory(Product.Shampoo, 5))
    //     .Returns(true);

    EXPECT_CALL(storeMock, HasEnoughInventory(Product::Shampoo, 5))
        .Times(1)
        .WillRepeatedly(Return(true));

    EXPECT_CALL(storeMock, RemoveInventory(Product::Shampoo, 5)).Times(1);

    auto customer = Customer();

    bool success = customer.Purchase(storeMock, Product::Shampoo, 5);

    ASSERT_TRUE(success);
    // storeMock.Verify(
    //     x = > x.RemoveInventory(Product.Shampoo, 5),
    //     Times.Once);
};

 
