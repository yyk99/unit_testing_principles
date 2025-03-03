#include <gtest/gtest.h>

class Product
{
private:
    std::string _name;

public:
    Product(std::string const& name)
        : _name(name)
    {
    }

    bool operator == (Product const& other)const {
        return other._name == this->_name;
    }
};


class Order
{
private:
    std::vector<Product> _products;

public:
    std::vector<Product> const& Products() const { return _products; };

public:
    void AddProduct(Product const& product)
    {
        _products.push_back(product);
    }
};

class CustomerControllerTests2 : public testing::Test
{
};

// [Fact]
TEST_F(CustomerControllerTests2, Adding_a_product_to_an_order)
{
    auto product = Product("Hand wash");
    auto sut = Order();

    sut.AddProduct(product);

    ASSERT_EQ(1, sut.Products().size());
    ASSERT_EQ(product, sut.Products().front());
}


