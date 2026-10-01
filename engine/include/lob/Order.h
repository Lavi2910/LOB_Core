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
    int64_t quantity;       ///< Number of units to trade.
    int64_t priceTicks;     ///< Price for the order in ticks.
    uint64_t seq;           ///< Arrival sequence, assigned by the engine. Defines time priority.
};
#endif //ORDER_H
