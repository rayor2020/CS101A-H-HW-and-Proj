#pragma once
#include <vector>
#include <iostream>
// Do NOT use `using namespace std;` globally.
// Fill in each function body where marked TODO.

// trim_trailing_evens: while vector non-empty and last element even, pop_back().
inline void trim_trailing_evens(std::vector<int>& v) {
    // TODO: pop trailing even numbers
    (void)v;
    // no-op skeleton
}

// print_index_if: if i is in range, print v[i] + '\n'; else print
// "OOB (checked [] path)\n".
inline void print_index_if(const std::vector<int>& v, std::size_t i) {
    // TODO: range-check and print accordingly
    (void)v; (void)i;
    std::cout << "OOB (checked [] path)\n";
}
