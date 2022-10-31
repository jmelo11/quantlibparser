cmake_minimum_required(VERSION 3.22)
project(quantlibparser LANGUAGES CXX)

find_package(pybind11)
find_package(QuantLib REQUIRED)
find_package(Boost REQUIRED)

pybind11_add_module(quantlibparser module.cpp)
target_link_libraries(quantlibparser PRIVATE QuantLib::QuantLib Boost::boost)