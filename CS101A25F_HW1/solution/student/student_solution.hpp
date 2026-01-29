#pragma once
// student/student_solution.hpp
// You ONLY submit this single file.
// Do NOT use `using namespace std;` globally.

#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>
#include <limits>
#include <cctype>
#include <iostream>

// --------------------- A. Pointers & Arrays ---------------------

// Count strictly positive values in [p, p+N) — pointer-only
inline int count_positive(const int* p, int N) {
    int cnt = 0;
    const int* e = p + N;
    for (; p < e; ++p) if (*p > 0) ++cnt;
    return cnt;
}

// Reverse [p, p+N) in-place — pointer-only
inline void reverse_inplace(int* p, int N) {
    if (N <= 1) return;
    int* L = p;
    int* R = p + N - 1;
    while (L < R) {
        int t = *L; *L = *R; *R = t;
        ++L; --R;
    }
}

// --------------------- A.2 2D Templates (no int**) ---------------------

template <std::size_t C>
inline int sum2d_knownC(int (*a)[C], int R) {
    int s = 0;
    for (int i = 0; i < R; ++i)
        for (std::size_t j = 0; j < C; ++j)
            s += a[i][j];
    return s;
}

template <std::size_t R, std::size_t C>
inline int sum2d_ref(const int (&a)[R][C]) {
    int s = 0;
    for (std::size_t i = 0; i < R; ++i)
        for (std::size_t j = 0; j < C; ++j)
            s += a[i][j];
    return s;
}

template <std::size_t R, std::size_t C>
inline void transpose(const int (&A)[R][C], int (&B)[C][R]) {
    for (std::size_t i = 0; i < R; ++i)
        for (std::size_t j = 0; j < C; ++j)
            B[j][i] = A[i][j];
}

// --------------------- B. References & Vectors ---------------------

inline void to_upper_ptr(char* first, char* last) {
    for (; first != last; ++first)
        *first = static_cast<char>(std::toupper(static_cast<unsigned char>(*first)));
}

inline void to_upper_ref(std::string& s) {
    for (char& c : s)
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
}

inline void trim_trailing_evens(std::vector<int>& v) {
    while (!v.empty() && v.back() % 2 == 0) v.pop_back();
}

inline void print_index_if(const std::vector<int>& v, std::size_t i) {
    if (i < v.size()) std::cout << v[i] << "\n";
    else std::cout << "OOB (checked [] path)\n";
}

// --------------------- C. Safe Values & Expressions ---------------------

// C.1 — PRINT values only (no UB)
inline void c1_print_limits_wrap() {
    using std::cout;
    auto i32_min = std::numeric_limits<std::int32_t>::min();
    auto i32_max = std::numeric_limits<std::int32_t>::max();
    auto u32_max = std::numeric_limits<std::uint32_t>::max();
    std::uint32_t wrap = static_cast<std::uint32_t>(u32_max + 1u);
    cout << "[C.1] int32_t min="  << i32_min
         << " max="               << i32_max  << "\n";
    cout << "[C.1] uint32_t max=" << u32_max  << "\n";
    cout << "[C.1] UINT32_MAX + 1 == " << wrap
         << " (wraps modulo 2^32)\n";
    cout << "      Note: signed overflow is undefined behavior; do not rely on wrap for signed types.\n";
}

// C.2 — safe addition (detect overflow using wider type)
inline bool add_safe(int x, int y, int& out) {
    long long sum = static_cast<long long>(x) + static_cast<long long>(y);
    if (sum < static_cast<long long>(std::numeric_limits<int>::min()) ||
        sum > static_cast<long long>(std::numeric_limits<int>::max()))
        return false;
    out = static_cast<int>(sum);
    return true;
}

// --------------------- Optional: PRINT-style demos ---------------------

// O.1 — PRINT vector after pointer-based mutation and reallocation info
inline void o1_print_bridge_invalidation() {
    using std::cout; using std::vector;
    int a[6]{1,2,3,4,5,6};
    vector<int> v(a, a+6);
    int* p = v.data();
    for (std::size_t i=0;i<v.size();++i) *(p+i) = -(*(p+i));  // mutate via pointer

    std::size_t old_cap = v.capacity();
    int* snap = v.data();
    while (v.capacity() == old_cap) v.push_back(0);

    cout << "================ [O1] Array <-> Vector Bridge & Pointer Invalidation ================\n";
    cout << "[O.1] vector after mutation/growth: [";
    for (std::size_t i=0;i<v.size();++i){ if(i) cout<<", "; cout<<v[i]; }
    cout << "]\n";
    cout << "       reallocated? " << std::boolalpha << (v.data()!=snap)
         << " (old cap=" << old_cap << ", new cap=" << v.capacity() << ")\n";
    cout << "       NOTE: reserve() enough capacity or re-fetch data() before using pointers again.\n";
}

// O.2 — PRINT a short paragraph
inline void o2_print_api_design_reflection() {
    std::cout
      << "[O.2] Pointers are preferable when nullability is meaningful, when expressing half-open ranges "
      << "([first,last)), or when interoperating with C APIs. References are better to express non-null "
      << "intent and object-centric APIs: use T& for mutation and const T& for read-only views. "
      << "Example pointer API: to_upper_ptr(char*,char*). Example reference API: to_upper_ref(std::string&)."
      << "\n";
}
