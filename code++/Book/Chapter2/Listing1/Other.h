#ifndef __OTHER_H
#define __OTHER_H

#include <map>
#include <stdexcept>

namespace book::chapter2::listing1 {
#if 0
}
#endif

enum Product
{
    Shampoo,
    Book
};

class Store
{
private:
    std::map<Product, int> _inventory;

public:
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
            _inventory[product] = quantity;
        }
    }

    int GetInventory(Product product)
    {
#if 0
        bool productExists = _inventory.TryGetValue(product, out int remaining);
        return productExists ? remaining : 0;
#else
        return _inventory.count(product);
#endif
    }
};

class Customer
{
public:
    bool Purchase(Store store, Product product, int quantity)
    {
        if (!store.HasEnoughInventory(product, quantity))
        {
            return false;
        }

        store.RemoveInventory(product, quantity);

        return true;
    }
};


} // namespace
#endif