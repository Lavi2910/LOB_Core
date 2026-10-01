#include <iostream>
#include <limits>
#include <lob/OrderBook.h>

void inject(OrderBook& ob, int64_t p, int64_t q, Side side, uint64_t id) {
    Order o;
    o.priceTicks = p;
    o.quantity = q;
    o.side = side;
    o.id = id;

    std::string sideStr = (side == Side::BUY) ? "BUY " : "SELL";
    std::cout << "[ENTRY] ID:" << id << " " << sideStr << " " << q << " @ " << p << std::endl;

    ob.createOrder(o);
}

int main() {
    OrderBook ob;

    std::cout << "--- Phase 1: Building Liquidity ---" << std::endl;
    inject(ob, 1005, 50, Side::BUY, 101);
    inject(ob, 1004, 30, Side::BUY, 102);
    inject(ob, 1012, 40, Side::SELL, 103);
    inject(ob, 1015, 25, Side::SELL, 104);

    std::cout << "\n--- Phase 2: Testing Cancel (ID 103: SELL 40 @ 1012) ---" << std::endl;
    ob.cancelOrder(103);
    std::cout << "[SYSTEM] Order 103 Canceled." << std::endl;

    std::cout << "\n--- Phase 3: Aggressive BUY (Should skip canceled 103) ---" << std::endl;
    inject(ob, 1020, 40, Side::BUY, 105);

    std::cout << "\n--- Phase 4: Final Liquidity Check ---" << std::endl;

    int64_t bestBid = ob.getBestBidPrice();
    int64_t bestAsk = ob.getBestAskPrice();

    std::cout << "Best Bid: " << (bestBid == -1 ? "No bids remaining" : std::to_string(bestBid)) << std::endl;
    std::cout << "Best Ask: " << (bestAsk == std::numeric_limits<int64_t>::max() ? "No asks remaining" : std::to_string(bestAsk)) << std::endl;

    ob.printSummary();

    return 0;
}