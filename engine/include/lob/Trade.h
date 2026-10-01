#ifndef TRADE_H
#define TRADE_H
#include <cstdint>
#include <lob/Order.h>


/**
 * @brief Represents a completed transaction between a buyer and a seller.
 * Contains all necessary data for completed trades.
 */
struct Trade {
    int64_t priceTicks;     ///< Price of the filled trade in ticks.
    int64_t quantity;       ///< Quantity traded.
    Side aggressorSide;     ///< The side who aggressed the trade.
    uint64_t buyerId;       ///< Order ID of the buyer.
    uint64_t sellerId;      ///< Order ID of the seller.
};
#endif