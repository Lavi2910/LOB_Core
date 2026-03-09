cmake_minimum_required(VERSION 3.31)
project(LOB_Core)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(LOB_Core
        src/main.cpp
        src/OrderBook.cpp
)