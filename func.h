#include <boost/python.hpp>
#include <NTL/ZZ.h>
#include <NTL/vector.h>
#include <NTL/tools.h>
#include <NTL/GF2.h>
// ___________________________________________________________________________ZZ
int NumBitsWrapperLong(long value) {
    ZZ zzValue(value);
    return NumBits(zzValue);
}

int NumBitsWrapperZZ(const ZZ& value) {
    return NumBits(value);
}

template<typename T>
bool equals(const Vec<T>& v1, const Vec<T>& v2) {
    return v1 == v2;
}

template<typename T>
bool not_equals(const Vec<T>& v1, const Vec<T>& v2) {
    return v1 != v2;
}

template<typename T>
std::string vec_to_string(const Vec<T>& v) {
    std::ostringstream oss;
    oss << v;
    return oss.str();
}
nikita@nikita:~/boosts/test3$ ./tst
Time taken by NTL::solve: 166609799 microseconds
The system is solvable.
nikita@nikita:~/boosts/test3$ ./tst
Time taken by NTL::solve: 165822917 microseconds
The system is solvable.
nikita@nikita:~/boosts/test3$ ./tst
Time taken by NTL::solve: 165625432 microseconds
The system is solvable.
//GCD
ZZ gcd_ZZ(const ZZ& a, const ZZ& b) {
    ZZ result;
    GCD(result, a, b);
    return result;
}

long gcd_long(const ZZ& a, long b) {
    ZZ result;
    GCD(result, a, ZZ(b));
    return conv<long>(result);
}

long gcd_long_long(long a, long b) {
    ZZ result;
    GCD(result, ZZ(a), ZZ(b));
    return conv<long>(result);
}

//vec
template <typename T>
struct VecWrapper {
    static T get_element(const Vec<T>& vec, long index) {
        if (index < 0 || index >= vec.length()) {
            throw std::out_of_range("Index out of range");
        }
        return T(vec[index]);
    }

    static void set_element(Vec<T>& vec, long index, const T& value) {
        if (index < 0 || index >= vec.length()) {
            throw std::out_of_range("Index out of range");
        }
        vec.put(index, value);
    }

    static void set_element_with_ZZ(Vec<T>& vec, long index, const python::object& value_obj) {
        if (python::extract<T>(value_obj).check()) {
            T value = python::extract<T>(value_obj);
            set_element(vec, index, value);
        } else {
            throw std::runtime_error("Invalid type for assignment");
        }
    }

    static std::string to_string(const Vec<T>& vec) {
        std::ostringstream oss;
        oss << vec;
        return oss.str();
    }
};
