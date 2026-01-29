#pragma once
#include <string>
// Do NOT use `using namespace std;` globally.
// Fill in each function body where marked TODO.

// to_upper_ptr: modify characters in [first,last) in place.
// Use std::toupper; ALWAYS cast to unsigned char before calling toupper to avoid UB.
inline void to_upper_ptr(char* first, char* last) {
    // TODO: walk from first to last (excluded) and uppercase each char
    (void)first; (void)last;
    // no-op skeleton
}

// to_upper_ref: iterate the std::string by reference and uppercase each element.
inline void to_upper_ref(std::string& s) {
    // TODO: uppercase each character in s
    (void)s;
    // no-op skeleton
}
