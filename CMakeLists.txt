cmake_minimum_required(VERSION 2.8)
project(Neuron)
set(CMAKE_CXX_FALGS "-W -Wall -pedantic -std=c++11")

enable_testing()
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable (neuron test_fun1.cpp neuron.cpp network.cpp)
add_executable (neuron_unittest neuron.cpp network.cpp neuron_unittest.cpp)

target_link_libraries(neuron_unittest gtest gtest_main)
add_test(neuron_unittest neuron_unittest)