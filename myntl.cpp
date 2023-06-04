#include <boost/python.hpp>
#include <NTL/ZZ.h>
#include <NTL/vector.h>
#include <NTL/tools.h>

using namespace NTL;

int NumBitsWrapperLong(long value) {
    ZZ zzValue(value);
    return NumBits(zzValue);
}

int NumBitsWrapperZZ(const ZZ& value) {
    return NumBits(value);
}

namespace python = boost::python;

// template<typename T>
// T get_item(Vec<T>& v, long i) {
//     return v[i];
// }

// template<typename T>
// void set_item(Vec<T>& v, long i, T const& value) {
//     v[i] = value;
// }

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

// template<typename T>
// struct VecWrapper
// {
//     static T get_element(const Vec<T>& vec, long index)
//     {
//         if (index < 0 || index >= vec.length()) {
//             throw std::out_of_range("Index out of range");
//         }
//         return vec[index];
//     }

//     static void set_element(Vec<T>& vec, long index, const T& value)
//     {
//         if (index < 0 || index >= vec.length()) {
//             throw std::out_of_range("Index out of range");
//         }
//         vec.put(index, value);
//     }
// };

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


template<typename T>
void define_vec(const std::string& name) {
    python::class_<Vec<T> >(name.c_str(), python::init<>())
        .def("length", &Vec<T>::length)
        .def("SetLength", static_cast<void (Vec<T>::*)(long) >(&Vec<T>::SetLength))
        .def("SetLength", static_cast<void (Vec<T>::*)(long, const T&) >(&Vec<T>::SetLength))
        .def("SetMaxLength", &Vec<T>::SetMaxLength)
        .def("kill", &Vec<T>::kill)
        .def("QuickSetLength", &Vec<T>::QuickSetLength)
        .def("FixAtCurrentLength", &Vec<T>::FixAtCurrentLength)
        //.def("__getitem__", &get_item<T>)
        //.def("__setitem__", &set_item<T>)
        //test {
        .def("__setitem__", &VecWrapper<T>::set_element)
        .def("__getitem__", &VecWrapper<T>::set_element_with_ZZ)
        .def("__str__", &VecWrapper<T>::to_string)
        //test }
        .def("get", static_cast<const T& (Vec<T>::*)(long) const>(&Vec<T>::get),
             python::return_value_policy<python::copy_const_reference>())
        .def("put", &Vec<T>::put)
        .def("append", static_cast<void (Vec<T>::*)(const T&)>(&Vec<T>::append))
        .def("append", static_cast<void (Vec<T>::*)(const Vec<T>&)>(&Vec<T>::append))
        //.def("append", &Vec<T>::append)
        ;
    python::def("__eq__", &equals<T>);
    python::def("__ne__", &not_equals<T>);
    //python::def("__str__", &vec_to_string<T>);
}

void define_ZZ(const std::string&  name) {
    namespace py = boost::python;
        py::class_<ZZ>("ZZ", py::init<long>())
            .def(py::init<>())
            .def(py::init<const ZZ&>())
            .def("swap", &ZZ::swap)
            //basic methods
            //output
            .def(str(py::self))
            //sum
            .def(py::self + long())
            .def(long() + py::self)
            .def(py::self + py::self)
            .def(py::self += long())
            .def(py::self += py::self)
            //minus
            .def(py::self - py::self)
            .def(py::self - long())
            .def(long() - py::self )
            .def(py::self -= long())
            .def(py::self -= py::self)
            //multiplication
            .def(py::self * py::self)
            .def(py::self * long())
            .def(long() - py::self )
            .def(py::self *= long())
            .def(py::self *= py::self)
            //division
            .def(py::self * py::self)
            .def(py::self * long())
            .def(long() * py::self )
            .def(py::self *= long())
            .def(py::self *= py::self)
            //modulo
            .def(py::self % py::self)
            .def(py::self % long())
            // AND
            .def(py::self & py::self)
            .def(py::self & long())
            .def(long() & py::self )
            .def(py::self &= long())
            .def(py::self &= py::self)
            // OR
            .def(py::self | py::self)
            .def(py::self | long())
            .def(long() | py::self )
            .def(py::self |= long())
            .def(py::self |= py::self)
            // XOR
            .def(py::self ^ py::self)
            .def(py::self ^ long())
            .def(long() ^ py::self )
            .def(py::self ^= long())
            .def(py::self ^= py::self)
            //comparsion
            .def(py::self < py::self)
            // MEMBER OTHER
            .def("kill", &ZZ::kill)
            .def("swap", &ZZ::swap)
            .def("pinned", &ZZ::pinned)
            .def("set_size", &ZZ::SetSize)
            .def("get_size", &ZZ::size)
            .def("is_null", &ZZ::null)
            .def("max_alloc", &ZZ::MaxAlloc)
            .def("single_precision", &ZZ::SinglePrecision)
            .def("wide_single_precision", &ZZ::WideSinglePrecision)
            .def("kill_big", &ZZ::KillBig);
            // OTHER
            //.def("num_bits", &NumBits)
            ;
            py::def("num_bits", py::make_function(NumBitsWrapperLong));
            py::def("num_bits", py::make_function(NumBitsWrapperZZ));
            py::def("is_odd", &IsOdd);

            py::def("sign", &sign);
            py::def("is_zero", &IsZero);
            py::def("is_one", &IsOne);
            py::def("sub_pos", &SubPos);
            py::def("negate", &negate);
}

BOOST_PYTHON_MODULE(myntl) {
    //ZZ
    define_ZZ("ZZ");
    //Vec
    define_vec<long>("VecLong");
    define_vec<ZZ>("VecZZ");
    define_vec<double>("VecDouble");
}