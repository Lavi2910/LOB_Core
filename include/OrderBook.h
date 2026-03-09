#ifndef ORDERBOOK_H
#define ORDERBOOK_H
#include "Order.h"
#include <iostream>
#include <queue>
#include <set>
#include <unordered_set>
#include "Trade.h"

struct AsksComparator {
    bool operator()(const Order &a, const Order &b) const {
        //Price-Time Priority: Low price first and then earlier on time.
        if (a.price == b.price && a.timestamp > b.timestamp) return true;
        if (b.price < a.price) return true;
        return false;
    }
};

struct BidsComparator {
    bool operator()(const Order &a, const Order &b) const {
        //Price-Time Priority: high price first and then earlier on time.
        if (a.price == b.price && a.timestamp > b.timestamp) return true;
        if (a.price < b.price) return true;
        return false;
    }
};

class OrderBook {
private:
    std::priority_queue<Order, std::vector<Order>, BidsComparator> bids;
    std::priority_queue<Order, std::vector<Order>, AsksComparator> asks;
    std::unordered_set<uint64_t> canceledOrders;
    std::vector<Trade> trades;

public:
    /**
     * @brief Creates and processes a new limit order.
     * Matches the order against the best available prices. Any remaining quantity
     * is added to the order book.
     * @param order Reference to the order object to be processed.
     */
    void createOrder(Order &order);

    /**
     * @brief Marks an order ID as canceled.
     * Implements the 'Lazy Deletion' pattern, allowing O(1) cancellation complexity.
     * @param orderId The unique identifier of the order.
     */
    void cancelOrder(uint64_t orderId);

    /**
     * @brief Prints a detailed summary of the trading session.
     * Includes Total Volume, Trade Count, and VWAP (Volume Weighted Average Price).
     */
    void printSummary() const;

    //Getters
    double getBestBidPrice() const;
    double getBestAskPrice() const;
    int32_t getBestBidQuantity() const;
    int32_t getBestAskQuantity() const;

    // Helper methods for internal matching logic
    void setBestBidQuantity(int32_t quantity);
    void setBestAskQuantity(int32_t quantity);
    void addBidOrder(const Order &order);
    void addAskOrder(const Order &order);
    void exhaustBuyOrder(Order &order);
    void exhaustSellOrder(Order &order);
};



#endif //ORDERBOOK_H
