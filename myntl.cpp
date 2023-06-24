#include <boost/python.hpp>
#include <NTL/ZZ.h>
#include <NTL/vector.h>
#include <NTL/tools.h>
#include <NTL/GF2.h>
#include <NTL/matrix.h>
#include <NTL/mat_ZZ.h>

using namespace NTL;

//namespace python = boost::python;
namespace py = boost::python;
// template<typename T>
// T get_item(Vec<T>& v, long i) {
//     return v[i];
// }

// template<typename T>
// void set_item(Vec<T>& v, long i, T const& value) {
//     v[i] = value;
// }


int NumBitsWrapperLong(long value) {
    ZZ zzValue(value);
    return NumBits(zzValue);
}

int NumBitsWrapperZZ(const ZZ& value) {
    return NumBits(value);
}



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
//CRT
long CRT_ZZ(ZZ& a, ZZ& p, const ZZ& A, const ZZ& P)
{
    return CRT(a, p, A, P);
}

long CRT_long(ZZ& a, ZZ& p, long A, long P)
{
    return CRT(a, p, A, P);
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

    static void set_element_with_ZZ(Vec<T>& vec, long index, const py::object& value_obj) {
        if (py::extract<T>(value_obj).check()) {
            T value = py::extract<T>(value_obj);
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
            .def(py::self %= py::self)
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
            // shifts
            .def(py::self >> long())                  // operator>>
            .def(py::self << long())                  // operator<<
            .def(py::self <<= long())                 // operator<<=
            .def(py::self >>= long())  
            // op =
            //.def(py::self = py::self)
            //.def(py::self = long())
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
            .def("kill_big", &ZZ::KillBig)
            // OTHER
            .def("NextPrime", static_cast<ZZ(*)(const ZZ&, long)>(&NextPrime))
            .def("NextPrime", static_cast<long(*)(long, long)>(&NextPrime))
            .def("NextPrime", static_cast<void(*)(ZZ&, const ZZ&, long)>(&NextPrime))
            //
            .def("RandomPrime_ZZ", &RandomPrime_ZZ)
            //
            .def("power", static_cast<ZZ(*)(const ZZ&, long)>(&power))
            .def("power", static_cast<void(*)(ZZ&, long, long)>(&power))
            .def("power", static_cast<void(*)(ZZ&, const ZZ&, long)>(&power))
            //
            .def("SqrRoot", static_cast<void(*)(ZZ&, const ZZ&)>(&SqrRoot))
            .def("SqrRoot", static_cast<ZZ(*)(const ZZ&)>(&SqrRoot))
            .def("SqrRoot", static_cast<long(*)(long)>(&SqrRoot))
            //
            .def("AddMod", static_cast<void(*)(ZZ&, const ZZ&, const ZZ&, const ZZ&)>(&AddMod))
            .def("AddMod", static_cast<ZZ(*)(const ZZ&, const ZZ&, const ZZ&)>(&AddMod))
            .def("AddMod", static_cast<void(*)(ZZ&, const ZZ&, long, const ZZ&)>(&AddMod))
            .def("AddMod", static_cast<ZZ(*)(const ZZ&, long, const ZZ&)>(&AddMod))
            .def("AddMod", static_cast<void(*)(ZZ&, long, const ZZ&, const ZZ&)>(&AddMod))
            .def("AddMod", static_cast<ZZ(*)(long, const ZZ&, const ZZ&)>(&AddMod))
            //
            .def("SubMod", static_cast<void(*)(ZZ&, const ZZ&, const ZZ&, const ZZ&)>(&SubMod))
            .def("SubMod", static_cast<ZZ(*)(const ZZ&, const ZZ&, const ZZ&)>(&SubMod))
            .def("SubMod", static_cast<void(*)(ZZ&, const ZZ&, long, const ZZ&)>(&SubMod))
            .def("SubMod", static_cast<ZZ(*)(const ZZ&, long, const ZZ&)>(&SubMod))
            .def("SubMod", static_cast<void(*)(ZZ&, long, const ZZ&, const ZZ&)>(&SubMod))
            .def("SubMod", static_cast<ZZ(*)(long, const ZZ&, const ZZ&)>(&SubMod))
            //
            .def("MulMod", static_cast<void(*)(ZZ&, const ZZ&, const ZZ&, const ZZ&)>(&MulMod))
            .def("MulMod", static_cast<ZZ(*)(const ZZ&, const ZZ&, const ZZ&)>(&MulMod))
            .def("MulMod", static_cast<void(*)(ZZ&, const ZZ&, long, const ZZ&)>(&MulMod))
            .def("MulMod", static_cast<ZZ(*)(const ZZ&, long, const ZZ&)>(&MulMod))
            .def("MulMod", static_cast<void(*)(ZZ&, long, const ZZ&, const ZZ&)>(&MulMod))
            .def("MulMod", static_cast<ZZ(*)(long, const ZZ&, const ZZ&)>(&MulMod))
            //
            .def("SqrMod", static_cast<void(*)(ZZ&, const ZZ&, const ZZ&)>(&SqrMod))
            .def("SqrMod", static_cast<ZZ(*)(const ZZ&, const ZZ&)>(&SqrMod))
            //
            .def("InvMod", static_cast<ZZ(*)(const ZZ&, const ZZ&)>(&InvMod))
            .def("InvMod", static_cast<void(*)(ZZ&, const ZZ&, const ZZ&)>(&InvMod))
            .def("InvMod", static_cast<long(*)(long, long)>(&InvMod))
            //
            .def("PowerMod", static_cast<void(*)(ZZ&, const ZZ&, const ZZ&, const ZZ&)>(&PowerMod))
            .def("LowLevelPowerMod", static_cast<void(*)(ZZ&, const ZZ&, const ZZ&, const ZZ&)>(&LowLevelPowerMod))
            .def("PowerMod", static_cast<ZZ(*)(const ZZ&, const ZZ&, const ZZ&)>(&PowerMod))
            .def("PowerMod", static_cast<void(*)(ZZ&, const ZZ&, long, const ZZ&)>(&PowerMod))
            .def("PowerMod", static_cast<ZZ(*)(const ZZ&, long, const ZZ&)>(&PowerMod))
            .def("PowerMod", static_cast<long(*)(long, long, long)>(&PowerMod))
            //
            .def("Jacobi", &Jacobi)
            //
            .def("SqrRootMod", static_cast<void(*)(ZZ&, const ZZ&, const ZZ&)>(&SqrRootMod))
            .def("SqrRootMod", static_cast<ZZ(*)(const ZZ&, const ZZ&)>(&SqrRootMod))
            ;
            //GCD
            py::def("GCD", static_cast<ZZ (*)(const ZZ&, const ZZ&)>(&GCD));
            py::def("GCD", static_cast<long (*)(const ZZ&, long)>(&gcd_long));
            py::def("GCD", &gcd_long_long);
            
            py::def("num_bits", py::make_function(NumBitsWrapperLong));
            py::def("num_bits", py::make_function(NumBitsWrapperZZ));
            py::def("is_odd", &IsOdd);
            //
            py::def("CRT", static_cast<long (*)(ZZ&, ZZ&, const ZZ&, const ZZ&)>(CRT));
            py::def("CRT", static_cast<long (*)(ZZ&, ZZ&, long, long)>(CRT));

}

// Overloaded operators
// template <typename T>
// struct MatWrapper {
//     static T get_element(const Mat<T>& mat, long i, long j) {
//         if (i < 0 || i >= mat.NumRows() || j < 0 || j >= mat.NumCols()) {
//             throw std::out_of_range("Index out of range");
//         }
//         return T(mat[i][j]);
//     }
// };

template<typename T>
void define_vec(const std::string& name) {
    py::class_<Vec<T> >(name.c_str(), py::init<>())
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
        .def("__setitem__", &VecWrapper<T>::set_element_with_ZZ)
        .def("__getitem__", &VecWrapper<T>::get_element)
        .def("__str__", &VecWrapper<T>::to_string)
        //test }
        .def("get", static_cast<const T& (Vec<T>::*)(long) const>(&Vec<T>::get),
             py::return_value_policy<py::copy_const_reference>())
        .def("put", &Vec<T>::put)
        .def("append", static_cast<void (Vec<T>::*)(const T&)>(&Vec<T>::append))
        .def("append", static_cast<void (Vec<T>::*)(const Vec<T>&)>(&Vec<T>::append))
        //.def("append", &Vec<T>::append)
        ;
    py::def("__eq__", &equals<T>);
    py::def("__ne__", &not_equals<T>);
    //python::def("__str__", &vec_to_string<T>);
}

template<typename T>
py::list get_row(NTL::Mat<T>& self, long i) {
    py::list result;
    for (long j = 0; j < self.NumCols(); ++j) {
        result.append(self[i][j]);
    }
    return result;
}

// For operator <<
template<typename T>
std::string mat_to_string(NTL::Mat<T> const& self) {
    std::ostringstream oss;
    oss << self;
    return oss.str();
}

template<typename T>
void read_from_string(NTL::Mat<T>& self, std::string const& s) {
    std::istringstream iss(s);
    iss >> self;
}
// get and set
// template<typename T>
// void set_row(NTL::Mat<T>& self, long i, py::list const& lst) {
//     for (long j = 0; j < py::len(lst); ++j) {
//         self.put(i, j, static_cast<T>(py::extract<T>(lst[j])));
//     }
//}

template<typename T>
void set_item(NTL::Mat<T>& self, py::tuple t, T value) {
    long i = py::extract<long>(t[0]);
    long j = py::extract<long>(t[1]);
    self[i][j] = value;
}


// Expose to Python
template<typename T>
void define_mat(std::string const& name) {
    py::class_<NTL::Mat<T>>(name.c_str())
        .def(py::init<>())
        .def(py::init<const Mat<T>&>())
        .def("__getitem__", &get_row<T>)
        .def("__setitem__", static_cast<void(*)(NTL::Mat<T>&, py::tuple, T)>(&set_item<T>))
        .def(str(py::self))
        .def("SetDims", &Mat<T>::SetDims)
        .def("NumRows", &Mat<T>::NumRows)
        .def("NumCols", &Mat<T>::NumCols)
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("swap", &Mat<T>::swap)
        .def("move", &Mat<T>::move)
        .def("kill", &Mat<T>::kill)
        .def("MakeMatrix", static_cast<void(*)(NTL::Mat<T>&, const NTL::Vec< Vec<T> >& a)>(&NTL::MakeMatrix))
        .def("read_from_string", &read_from_string<T>)
        .def(py::self + py::self)
        .def(py::self - py::self)
        .def(py::self * py::self)
        .def(py::self * long())
        .def(py::self * NTL::ZZ())
        .def(NTL::ZZ() * py::self)
        .def(long() * py::self)
        .def(-py::self)
        .def(py::self * NTL::Vec<T>())
        .def(NTL::Vec<T>() * py::self)
        .def(py::self += py::self)
        .def(py::self -= py::self)
        .def(py::self *= py::self)
        .def(py::self *= T())
        .def(py::self *= py::self)
        .def(py::self *= long())
        .def("ident", static_cast<void(*)(NTL::Mat<T>&, long)>(&NTL::ident))
        .def("ident", static_cast<NTL::Mat<T>(*)(long)>(&NTL::ident_mat_ZZ))
        .def("diag", static_cast<void(*)(NTL::Mat<NTL::ZZ>&, long, const NTL::ZZ&)>(&NTL::diag))
        .def("diag", static_cast<NTL::mat_ZZ(*)(long, const NTL::ZZ&)>(&NTL::diag))
        .def("IsIdent", static_cast<long(*)(const NTL::Mat<NTL::ZZ>&, long)>(&NTL::IsIdent))
        .def("IsDiag", static_cast<long(*)(const NTL::Mat<NTL::ZZ>&, long, const NTL::ZZ&)>(&NTL::IsDiag))
        .def("determinant", static_cast<void(*)(NTL::ZZ&, const NTL::Mat<NTL::ZZ>&, long)>(&NTL::determinant))
        .def("determinant", static_cast<NTL::ZZ(*)(const NTL::Mat<NTL::ZZ>&, long)>(&NTL::determinant))
        .def("solve", static_cast<void(*)(NTL::ZZ&, NTL::Vec<NTL::ZZ>&, const NTL::Mat<NTL::ZZ>&, const NTL::Vec<NTL::ZZ>&, long)>(&NTL::solve))
        .def("solve1", static_cast<void(*)(NTL::ZZ&, NTL::Vec<NTL::ZZ>&, const NTL::Mat<NTL::ZZ>&, const NTL::Vec<NTL::ZZ>&)>(&NTL::solve1))
        .def("HenselSolve1", &HenselSolve1)
        
        // inv
        .def("inv", static_cast<void(*)(NTL::ZZ&, NTL::Mat<NTL::ZZ>&, const NTL::Mat<NTL::ZZ>&, long)>(&NTL::inv))
        .def("inv", static_cast<void(*)(NTL::Mat<NTL::ZZ>&, const NTL::Mat<NTL::ZZ>&)>(&NTL::inv))
        .def("inv", static_cast<NTL::Mat<NTL::ZZ>(*)(const NTL::Mat<NTL::ZZ>&)>(&NTL::inv))

        // sqr
        .def("sqr", static_cast<void(*)(NTL::Mat<NTL::ZZ>&, const NTL::Mat<NTL::ZZ>&)>(&NTL::sqr))
        .def("sqr", static_cast<NTL::Mat<NTL::ZZ>(*)(const NTL::Mat<NTL::ZZ>&)>(&NTL::sqr))

        // power
        .def("power", static_cast<void(*)(NTL::Mat<NTL::ZZ>&, const NTL::Mat<NTL::ZZ>&, const NTL::ZZ&)>(&NTL::power))
        .def("power", static_cast<NTL::Mat<NTL::ZZ>(*)(const NTL::Mat<NTL::ZZ>&, const NTL::ZZ&)>(&NTL::power))
        .def("power", static_cast<void(*)(NTL::Mat<NTL::ZZ>&, const NTL::Mat<NTL::ZZ>&, long)>(&NTL::power))
        .def("power", static_cast<NTL::Mat<NTL::ZZ>(*)(const NTL::Mat<NTL::ZZ>&, long)>(&NTL::power))
        // transpose
        .def("transpose", static_cast<void(*)(NTL::Mat<NTL::ZZ>&, const NTL::Mat<NTL::ZZ>&)>(&NTL::transpose))
        .def("transpose", static_cast<NTL::Mat<NTL::ZZ>(*)(const NTL::Mat<NTL::ZZ>&)>(&NTL::transpose))

        // conv
        .def("conv", static_cast<void(*)(NTL::mat_zz_p&, const NTL::Mat<NTL::ZZ>&)>(&NTL::conv))
        .def("conv", static_cast<void(*)(NTL::mat_ZZ_p&, const NTL::Mat<NTL::ZZ>&)>(&NTL::conv))

        // to_mat_zz_p
        .def("to_mat_zz_p", static_cast<NTL::mat_zz_p(*)(const NTL::Mat<NTL::ZZ>&)>(&NTL::to_mat_zz_p))

        // to_mat_ZZ_p
        .def("to_mat_ZZ_p", static_cast<NTL::mat_ZZ_p(*)(const NTL::Mat<NTL::ZZ>&)>(&NTL::to_mat_ZZ_p))

        // CRT
        .def("CRT", static_cast<long(*)(NTL::Mat<NTL::ZZ>&, NTL::ZZ&, const NTL::mat_zz_p&)>(&NTL::CRT))


        ;
}

BOOST_PYTHON_MODULE(myntl) {
    //ZZ
    define_ZZ("ZZ");
    //Vec
    define_vec<long>("VecLong");
    define_vec<ZZ>("VecZZ");
    define_vec<double>("VecDouble");
    //Mat
    define_mat<ZZ>("Mat_ZZ");
}