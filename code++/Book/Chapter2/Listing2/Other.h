#ifndef LISTING2_OTHER_H
#define LISTING2_OTHER_H

#include <map>
#include <stdexcept>

namespace book::chapter2::listing2 {
#if 0
}
#endif

enum Product
{
    Shampoo,
    Book
};

class IStore
{
public:
    virtual ~IStore() {};

    virtual bool HasEnoughInventory(Product product, int quantity) = 0;
    virtual void RemoveInventory(Product product, int quantity)  = 0;
    virtual void AddInventory(Product product, int quantity) = 0;
    virtual int GetInventory(Product product) = 0;
};

class Store : public IStore
{
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
        auto pos = _inventory.find(product);
        int cnt = (pos != _inventory.end() ? pos->second : 0);
        // printf("cnt == %d\n", cnt);
        return cnt;
    }
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
};


} // namespace

#endif
