#pragma once
#include <cstddef>
// Do NOT use `using namespace std;` globally.
// Fill in each function body where marked TODO.

template <std::size_t C>
inline int sum2d_knownC(int (*a)[C], int R) {
    // TODO: accumulate all elements a[i][j] for i in [0,R), j in [0,C)
    (void)a; (void)R;
    return 0;
}

template <std::size_t R, std::size_t C>
inline int sum2d_ref(const int (&a)[R][C]) {
    // TODO: accumulate all elements a[i][j]
    (void)a;
    return 0;
}

template <std::size_t R, std::size_t C>
inline void transpose(const int (&A)[R][C], int (&B)[C][R]) {
    // TODO: write B[j][i] = A[i][j]
    (void)A; (void)B;
    // no-op skeleton
}
