#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <vector>

typedef double decimal;
class Product
{
private:
    std::string _name;

public:
    Product(std::string name)
    {
        _name = name;
    }
};

class PriceEngine
{
public:
    decimal CalculateDiscount(std::vector<Product> product)
    {
        decimal discount = product.size() * 0.01;
        return std::min(discount, 0.2);
    }
};

class CustomerControllerTests
{
}

// [Fact]
TEST_F(CustomerControllerTests, Discount_of_two_products)
{
    auto product1 = Product("Hand wash");
    auto product2 = Product("Shampoo");
    auto sut = PriceEngine();

    decimal discount = sut.CalculateDiscount(
        {product1, product2}
    );

    ASSERT_DOUBLE_EQ(0.02, discount);
};
