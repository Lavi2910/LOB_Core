# LOB-Core | High-Performance Matching Engine in C++20

> A Limit Order Book is the core matching engine behind every stock exchange — 
> it pairs buyers and sellers in real time based on price and arrival order. 
> This implementation prioritizes the two operations that matter most in HFT: 
> fast insertions and near-instant cancellations.

A fast, memory-efficient Limit Order Book (LOB) implementation designed for high-frequency trading (HFT) scenarios. This project focuses on minimizing latency in order cancellation and providing trading analytics.

## 🚀 Key Technical Features
- **Price-Time Priority:** Orders are matched based on the best available price and the sequence in which they were received.
- **$O(1)$ Cancellation (Lazy Deletion):** Implements an optimized cancellation pattern using `std::unordered_set`. By marking orders as canceled rather than removing them from the middle of a heap, the engine maintains constant-time cancellation complexity.
- **Efficient Matching Logic:** Uses custom-comparatored `std::priority_queue` (Max-Heap for Bids, Min-Heap for Asks) to achieve $O(\log n)$ insertion and $O(1)$ access to the best prices.
- **VWAP Analytics:** Calculation of the **Volume Weighted Average Price** to provide session performance benchmarks.

## 📊 Performance Metrics
The engine is designed to handle aggressive "market sweeps" and partial fills efficiently. Every trade is recorded in a dedicated audit trail, allowing for detailed session summaries:
- **Total Traded Volume**
- **Trade Count**
- **VWAP Calculation:**
$$VWAP = \frac{\sum (Price \times Quantity)}{\sum Quantity}$$

## 🛠 Tech Stack & Concepts
- **Language:** Modern C++20 (using concepts like `enum class` and `std::unordered_set::contains`).
- **Data Structures:** Heaps (Priority Queues), Hash Sets, Vectors.
- **Design Patterns:** Lazy Deletion, Decoupled Header/Implementation.
- **Build System:** CMake.

  ## 📟 Sample Output

```
--- Phase 1: Building Liquidity ---
[ENTRY] ID:101 BUY  50 @ 100.5
[ENTRY] ID:102 BUY  30 @ 100.4
[ENTRY] ID:103 SELL 40 @ 101.2
[ENTRY] ID:104 SELL 25 @ 101.5
--- Phase 2: Testing Cancel (ID 103: SELL 40 @ 101.2) ---
[SYSTEM] Order 103 Canceled.
--- Phase 3: Aggressive BUY (Should skip canceled 103) ---
[ENTRY] ID:105 BUY  40 @ 102
   >>> [TRADE] Executed 25 units @ 101.5
--- Phase 4: Final Liquidity Check ---
Best Bid: 102.000000
Best Ask: No asks remaining
========================================
       TRADING SESSION SUMMARY
========================================
Total Trades Executed: 1
Total Volume Traded:   25 units
VWAP (Average Price):  101.5
Closing Price:         101.5
========================================
```

## 📂 Project Structure
- `include/`: Header files with Doxygen-style documentation (`@brief`, `@param`).
- `src/`: Core implementation of the matching engine and execution logic.
- `main.cpp`: Stress-testing suite including order injection and cancellation tests.

## ⚙️ Build and Run

To build the project, ensure you have a C++20 compatible compiler and CMake installed:
```bash
mkdir build && cd build
cmake ..
make
./LOB_Core
```
<img width="1360" height="1040" alt="lob_core_architecture" src="https://github.com/user-attachments/assets/bd5a4bdc-001f-42f4-9a37-97fd8fd83076" />
