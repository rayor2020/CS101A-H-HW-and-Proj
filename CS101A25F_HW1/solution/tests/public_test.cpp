#ifndef STUDENT_HEADER
#define STUDENT_HEADER student/student_solution.hpp
#endif
#define STR2(x) #x
#define STR(x)  STR2(x)
#include STR(STUDENT_HEADER)

#include <iostream>
#include <vector>
#include <string>
#include <cstddef>
#include <cstdint>

template <class T>
static void print_vec(const std::vector<T>& v, const char* label=nullptr) {
    if (label) std::cout << label;
    std::cout << "[";
    for (std::size_t i = 0; i < v.size(); ++i) {
        if (i) std::cout << ", ";
        std::cout << v[i];
    }
    std::cout << "]";
}

int main() {
    std::cout << "================ [A] Pointers & Arrays ================\n";
    {
        int buf[8]{-1, 2, 3, -4, 5, 0, 7, -8};
        std::cout << "[A.1] count_positive: " << count_positive(buf, 8) << "\n";
        std::cout << "[A.1] reverse_inplace before: ";
        print_vec(std::vector<int>(buf, buf+8)); std::cout << "\n";
        reverse_inplace(buf, 8);
        std::cout << "[A.1] reverse_inplace after : ";
        print_vec(std::vector<int>(buf, buf+8)); std::cout << "\n";
    }
    {
        int m[2][3]{{1,2,3},{4,5,6}};
        int mt[3][2]{};
        std::cout << "[A.2] sum2d_ref: " << sum2d_ref(m) << "\n";
        std::cout << "[A.2] sum2d_knownC(C=3): " << sum2d_knownC<3>(m, 2) << "\n";
        transpose(m, mt);
        std::cout << "[A.2] transpose 2x3 -> 3x2:\n";
        for (int r = 0; r < 3; ++r) {
            std::cout << "      ";
            for (int c = 0; c < 2; ++c) std::cout << mt[r][c] << " ";
            std::cout << "\n";
        }
    }

    std::cout << "================ [B] References & Vectors ================\n";
    {
        std::string s = "HeLlo!";
        std::string t = s;
        to_upper_ref(s);
        std::cout << "[B.1] to_upper_ref: \"HeLlo!\" -> \"" << s << "\"\n";
        if (!t.empty()) {
            to_upper_ptr(&t[0], &t[0] + static_cast<std::ptrdiff_t>(t.size()));
            std::cout << "      to_upper_ptr: -> \"" << t << "\"\n";
        }
    }
    {
        std::vector<int> v{2,4,6,7,9,10,12};
        print_vec(v, "[B.2] before trim: "); std::cout << "\n";
        trim_trailing_evens(v);
        print_vec(v, "       after  trim: "); std::cout << "\n";
        std::cout << "       print_index_if(100): ";
        print_index_if(v, 100);
    }

    std::cout << "================ [C] Safe Values & Expressions ================\n";
    {
        c1_print_limits_wrap(); // C.1 prints values
        int out = -1;
        bool ok1 = add_safe(123, 456, out);
        std::cout << "[C.2] add_safe(123,456) -> ok=" << ok1 << " sum=" << (ok1 ? std::to_string(out) : "n/a") << "\n";
        bool ok2 = add_safe(1500000000, 1500000000, out);
        std::cout << "       add_safe(1.5e9,1.5e9) -> ok=" << ok2 << (ok2 ? "" : " (overflow)") << "\n";
    }

    std::cout << "================ [O] Optional Extensions ================\n";
    {
        o1_print_bridge_invalidation(); // prints vector & reallocation info
        o2_print_api_design_reflection();
    }
    return 0;
}
