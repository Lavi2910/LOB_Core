# Matching engine as a library: the demo, tests and benchmarks all link against it.
add_library(lob_engine
    src/OrderBook.cpp
)
target_include_directories(lob_engine PUBLIC include)
target_compile_features(lob_engine PUBLIC cxx_std_20)
target_compile_options(lob_engine PRIVATE -Wall -Wextra -Wpedantic)

add_executable(lob_demo apps/demo.cpp)
target_link_libraries(lob_demo PRIVATE lob_engine)
