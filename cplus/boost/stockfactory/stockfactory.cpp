#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <boost/bind.hpp>
#include <map>
#include <cassert>
#include "../lock/lock.h"

class Stock
{
private:
    std::string _key;
public:
    Stock()
    {}

    Stock(std::string key) : _key(key)
    {}

    std::string key()
    {
        return _key;
    }
};

class StockFactory : public boost::enable_shared_from_this<StockFactory>, boost::noncopyable
{
private:
    mutable MutexLock _lock;

    typedef std::map<std::string, boost::weak_ptr<Stock> > container;
    container _stocks;
    //typedef container::iterator iterator;

    void removeStock(Stock *stock)
    {
        if(stock)
        {
            MutexLockGuard lock(_lock);
            _stocks.erase(stock->key());
        }
    }

    static void weakDeleteCallback(const boost::weak_ptr<StockFactory>& wkFactory, Stock *stock)
    {
        boost::shared_ptr<StockFactory> factory = wkFactory.lock();
        if(factory)
        {
            factory->removeStock(stock);
        }
        delete stock;
    }

public:
    StockFactory()
    {}

    boost::shared_ptr<Stock> get(const std::string &key)
    {
        boost::shared_ptr<Stock> pStock;
        MutexLockGuard guard(_lock);
        boost::weak_ptr<Stock>& weak_stock = _stocks[key];
        pStock = weak_stock.lock();
        if(!pStock)
        {
            pStock.reset(new Stock(key),
                boost::bind(&StockFactory::weakDeleteCallback, boost::weak_ptr<StockFactory>(shared_from_this()), _1));
            weak_stock = pStock;
        }
        return pStock;
    }

    virtual ~StockFactory()
    {}
};

void test_long_life_factory()
{
    boost::shared_ptr<StockFactory> factory(new StockFactory);
    {
        boost::shared_ptr<Stock> stock = factory->get("NYSE:IBM");
        boost::shared_ptr<Stock> stock2 = factory->get("NYSE:IBM");
        assert(stock == stock2);
    }
}

void test_short_life_factory()
{
    boost::shared_ptr<Stock> stock;
    {
        boost::shared_ptr<StockFactory> factory(new StockFactory);
        stock = factory->get("NYSE:IBM");
        boost::shared_ptr<Stock> stock2 = factory->get("NYSE:IBM");
        assert(stock == stock2);
    }
}

int main()
{
    test_long_life_factory();
    test_short_life_factory();
    return 0;
}


