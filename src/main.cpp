#include <iostream>
#include "../include/OrderBook.h"

void inject(OrderBook& ob, double p, int32_t q, Side side, uint64_t id) {
    Order o;
    o.price = p;
    o.quantity = q;
    o.side = side;
    o.id = id; o.timestamp = 1000 + id;

    std::string sideStr = (side == Side::BUY) ? "BUY " : "SELL";
    std::cout << "[ENTRY] ID:" << id << " " << sideStr << " " << q << " @ " << p << std::endl;

    ob.createOrder(o);
}

int main() {
    OrderBook ob;

    std::cout << "--- Phase 1: Building Liquidity ---" << std::endl;
    inject(ob, 100.5, 50, Side::BUY, 101);
    inject(ob, 100.4, 30, Side::BUY, 102);
    inject(ob, 101.2, 40, Side::SELL, 103);
    inject(ob, 101.5, 25, Side::SELL, 104);

    std::cout << "\n--- Phase 2: Testing Cancel (ID 103: SELL 40 @ 101.2) ---" << std::endl;
    ob.cancelOrder(103);
    std::cout << "[SYSTEM] Order 103 Canceled." << std::endl;

    std::cout << "\n--- Phase 3: Aggressive BUY (Should skip canceled 103) ---" << std::endl;
    inject(ob, 102.0, 40, Side::BUY, 105);

    std::cout << "\n--- Phase 4: Final Liquidity Check ---" << std::endl;
    std::cout << "Best Bid: " << ob.getBestBidPrice() << std::endl;
    std::cout << "Best Ask: " << ob.getBestAskPrice() << std::endl;

    ob.printSummary();

    return 0;
}