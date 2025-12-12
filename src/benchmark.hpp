#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include "board.hpp"
#include "engine.hpp"
#include <functional>

template<typename T> std::chrono::milliseconds time_function(T f, int count);
std::chrono::milliseconds time_do_move(int count);



void benchmark(long count);

#endif