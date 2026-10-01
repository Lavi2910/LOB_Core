#ifndef ORDER_H
#define ORDER_H
#include <cstdint>

/**
 * @brief Represents the side of the market for a given order.
 */
enum class Side {BUY, SELL};

/**
 * @brief Represents a single Limit Order in the matching engine.
 * Contains all necessary data for price-time priority matching.
 */
struct Order {
    uint64_t id;            ///< Unique identifier for the order (64-bit to prevent overflow).
    Side side;              ///< BUY or SELL.
    int32_t quantity;       ///< Number of units to trade.
    double price;           ///< Price for the order.
    uint64_t timestamp;     ///< Time of entry for priority.
};
#endif //ORDER_H
