#include <lob/OrderBook.h>
#include <limits>

using namespace std;

int64_t OrderBook::getBestAskPrice() const {
    if (this->asks.empty()) {
        return numeric_limits<int64_t>::max();
    }
    return this->asks.top().priceTicks;
}

int64_t OrderBook::getBestBidPrice() const {
    if (this->bids.empty()) {
        return -1;
    }
    return this->bids.top().priceTicks;
}

int64_t OrderBook::getBestBidQuantity() const {
    if (this->bids.empty()) {
        return -1;
    }
    return this->bids.top().quantity;
}

int64_t OrderBook::getBestAskQuantity() const {
    if (this->asks.empty()) {
        return numeric_limits<int64_t>::max();
    }
    return this->asks.top().quantity;
}

void OrderBook::setBestBidQuantity(int64_t quantity) {
    if (quantity == 0) {
        bids.pop();
    }else {
        Order order = bids.top();
        bids.pop();
        order.quantity = quantity;
        bids.push(order);
    }
}
void OrderBook::setBestAskQuantity(int64_t quantity) {
    if (quantity == 0) {
        asks.pop();
    }else {
        Order order = asks.top();
        asks.pop();
        order.quantity = quantity;
        asks.push(order);
    }
}

void OrderBook::addBidOrder(const Order &order) {
    this->bids.push(order);
}

void OrderBook::addAskOrder(const Order &order) {
    this->asks.push(order);
}

bool static isBuySide(const Order &order) {
    return order.side == Side::BUY;
}

void OrderBook::exhaustBuyOrder(Order &order) {
    while (!this->asks.empty() && this->getBestAskPrice() <= order.priceTicks && order.quantity > 0) {
        // Check for canceled orders at the top of the heap (Lazy Deletion).
        // This avoids the expensive O(N) operation of removing an element from the middle of a heap.
        if (this->canceledOrders.contains(this->asks.top().id)) {
            this->canceledOrders.erase(this->asks.top().id);
            this->asks.pop();
            continue;// Move to the next best price level
        }
        int64_t matchQuantity = min(order.quantity, this->getBestAskQuantity());
        if (matchQuantity > 0) {
            this->trades.push_back({
                this->asks.top().priceTicks,
                matchQuantity,
                Side::BUY,
                order.id,
                this->asks.top().id
            });
        }
        std::cout << "   >>> [TRADE] Executed " << matchQuantity << " units @ "
                  << this->getBestAskPrice()
                  << std::endl;
        this->setBestAskQuantity(this->getBestAskQuantity() - matchQuantity);
        order.quantity -= matchQuantity;
    }
}

void OrderBook::exhaustSellOrder(Order &order) {
    while (!this->bids.empty() && this->getBestBidPrice() >= order.priceTicks && order.quantity > 0) {
        // Check for canceled orders at the top of the heap (Lazy Deletion).
        // This avoids the expensive O(N) operation of removing an element from the middle of a heap.
        if (this->canceledOrders.contains(this->bids.top().id)) {
            this->canceledOrders.erase(this->bids.top().id);
            this->bids.pop();
            continue;// Move to the next best price level
        }
        int64_t matchQuantity = min(order.quantity, this->getBestBidQuantity());
        if (matchQuantity > 0) {
            this->trades.push_back({
                this->bids.top().priceTicks,
                matchQuantity,
                Side::SELL,
                this->bids.top().id,
                order.id
            });
        }
        std::cout << "   >>> [TRADE] Executed " << matchQuantity << " units @ "
                  << this->getBestBidPrice()
                  << std::endl;
        this->setBestBidQuantity(this->getBestBidQuantity() - matchQuantity);
        order.quantity -= matchQuantity;
    }
}

void OrderBook::createOrder(Order &order) {
    order.seq = nextSeq++;
    if (isBuySide(order)) {
        this->exhaustBuyOrder(order);
        if (order.quantity > 0) {
            this->addBidOrder(order);
        }
    }
    else {
        this->exhaustSellOrder(order);
        if (order.quantity > 0) {
            this->addAskOrder(order);
        }
    }
}

void OrderBook::cancelOrder(const uint64_t orderId) {
    this->canceledOrders.insert(orderId);
}

void OrderBook::printSummary() const {
    std::cout << "\n" << std::string(40, '=') << std::endl;
    std::cout << "       TRADING SESSION SUMMARY" << std::endl;
    std::cout << std::string(40, '=') << std::endl;
    std::cout << "Total Trades Executed: " << trades.size() << std::endl;

    double totalVolume = 0;
    double weightedSum = 0;

    for (const auto& t : trades) {
        totalVolume += t.quantity;
        weightedSum += (t.priceTicks * t.quantity);
    }

    if (totalVolume > 0) {
        std::cout << "Total Volume Traded:   " << totalVolume << " units" << std::endl;
        std::cout << "VWAP (Average Price):  " << (weightedSum / totalVolume) << std::endl;
        std::cout << "Closing Price:         " << trades.back().priceTicks << std::endl;
    } else {
        std::cout << "No trades were executed during this session." << std::endl;
    }
    std::cout << std::string(40, '=') << std::endl;
}