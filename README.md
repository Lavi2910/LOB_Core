# LOB-Core | High-Performance Matching Engine in C++20

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
