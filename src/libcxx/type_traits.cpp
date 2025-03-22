#include <type_traits>

namespace std {

namespace {

#define C(expr) static_assert(expr, #expr)

struct test_false : false_type { static constexpr bool test = false; };
struct test_true  : true_type  { static constexpr bool test = true;  };
enum test_enum {};
union test_union {
public:
    test_union();
};
class test_class {
public:
    test_class() noexcept;
    test_class(test_class const&) noexcept;
    test_class(test_class&&) noexcept;
};
struct test_struct {
    int test;
};
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunneeded-internal-declaration"
const auto test_lambda = [](){};
#pragma GCC diagnostic pop

// test type_identity
template<class T> void test_type_identity(integral_constant<T, 0>, type_identity_t<T>);
C((is_void_v<decltype(test_type_identity(bool_constant<false>{}, 0))>));

//------------------------------------------------------------------------------
// type relationships
//------------------------------------------------------------------------------

// test is_same
C((is_same_v<void, void>));
C((!is_same<void, void const>::value));
C((!is_same_v<void const, void() const>));

// test is_base_of
namespace test_is_base_of {
    class A {};
    class B : A {};
    class Z : B {};
    class D {};
    union E {};
    using I = int;

    C(( is_base_of_v<A, A>));
    C(( is_base_of_v<A, B>));
    C(( is_base_of_v<A, Z>));
    C((!is_base_of_v<A, D>));
    C((!is_base_of_v<B, A>));
    C((!is_base_of_v<E, E>));
    C((!is_base_of_v<I, I>));
}

// test is_convertible
namespace test_is_convertible {
    class E { public: template<class T> E(T&&) {} };
    static constexpr void __attribute__((unused)) test(void) {
        class A {};
        class B : public A {};
        class Z {};
        class D { public: operator Z() { return c; } Z c; };
        C((is_convertible_v<B*, A*>));
        C((!is_convertible_v<A*, B*>));
        C((is_convertible_v<D, Z>));
        C((!is_convertible_v<B*, Z*>));
        C((is_convertible_v<A, E>));
    }
}

//------------------------------------------------------------------------------
// logical operator traits
//------------------------------------------------------------------------------

// test conjunction
C((conjunction_v<>));
C((!conjunction<test_false>::test));
C((conjunction<test_true>::test));
C((!conjunction<test_false, false_type>::test));
C((!conjunction<test_false, true_type>::test));
C((!conjunction<true_type, test_false>::test));
C((conjunction<true_type, test_true>::test));
C((!conjunction<test_false, false_type, false_type>::test));
C((!conjunction<test_false, false_type, true_type>::test));
C((!conjunction<test_false, true_type, false_type>::test));
C((!conjunction<test_false, true_type, true_type>::test));
C((!conjunction<true_type, test_false, false_type>::test));
C((!conjunction<true_type, test_false, true_type>::test));
C((!conjunction<true_type, true_type, test_false>::test));
C((conjunction<true_type, true_type, test_true>::test));

// test disjunction
C((!disjunction_v<>));
C((!disjunction<test_false>::test));
C((disjunction<test_true>::test));
C((!disjunction<false_type, test_false>::test));
C((disjunction<false_type, test_true>::test));
C((disjunction<test_true, false_type>::test));
C((disjunction<test_true, true_type>::test));
C((!disjunction<false_type, false_type, test_false>::test));
C((disjunction<false_type, false_type, test_true>::test));
C((disjunction<false_type, test_true, false_type>::test));
C((disjunction<false_type, test_true, true_type>::test));
C((disjunction<test_true, false_type, false_type>::test));
C((disjunction<test_true, false_type, true_type>::test));
C((disjunction<test_true, true_type, false_type>::test));
C((disjunction<test_true, true_type, true_type>::test));

//------------------------------------------------------------------------------
// const/volatile removal traits
//------------------------------------------------------------------------------

// test negation
C((negation_v<false_type>));
C((!negation<true_type>::value));

// test remove_const
C((is_same_v<void, remove_const_t<void>>));
C((is_same_v<void, remove_const<void const>::type>));
C((is_same_v<void() const, remove_const_t<void() const>>));

// test remove_volatile
C((is_same_v<void, remove_volatile_t<void>>));
C((is_same_v<void, remove_volatile<void volatile>::type>));
C((is_same_v<void() volatile, remove_volatile_t<void() volatile>>));

// test remove_cv
C((is_same_v<void, remove_cv_t<void>>));
C((is_same_v<void, remove_cv<void const>::type>));
C((is_same_v<void, remove_cv_t<void volatile>>));
C((is_same_v<void, remove_cv<void const volatile>::type>));
C((is_same_v<void() const volatile, remove_cv_t<void() const volatile>>));

//------------------------------------------------------------------------------
// primary type categories
//------------------------------------------------------------------------------

// test is_void
C((is_void_v<void>));
C((is_void<void const>::value));
C((is_void_v<void volatile>));
C((is_void<void const volatile>::value));
C((!is_void_v<void() const>));

// test is_null_pointer
C((is_null_pointer_v<nullptr_t>));
C((is_null_pointer<nullptr_t const>::value));
C((is_null_pointer_v<nullptr_t volatile>));
C((is_null_pointer<nullptr_t const volatile>::value));
C((is_null_pointer_v<decltype(nullptr)>));
C((!is_null_pointer<decltype(NULL)>::value));
C((!is_null_pointer_v<nullptr_t() const>));

// test is_integral
C((is_integral_v<bool>));
C((is_integral<bool const>::value));
C((is_integral_v<bool volatile>));
C((is_integral<bool const volatile>::value));
C((is_integral_v<signed __int48>));
C((is_integral<unsigned __int48>::value));
C((!is_integral_v<void>));
C((!is_integral<nullptr_t>::value));
C((!is_integral_v<float>));
C((!is_integral<false_type>::value));
C((!is_integral_v<int() const>));

// test is_floating_point
C((is_floating_point_v<float>));
C((is_floating_point<float const>::value));
C((is_floating_point_v<double volatile>));
C((is_floating_point<long double const volatile>::value));
C((!is_floating_point_v<void>));
C((!is_floating_point<nullptr_t>::value));
C((!is_floating_point_v<int>));
C((!is_floating_point<true_type>::value));
C((!is_floating_point_v<float() const>));

// test is_enum
C((is_enum_v<test_enum>));
C((!is_enum<test_union>::value));
C((!is_enum_v<test_class>));
C((!is_enum<void>::value));
C((!is_enum_v<nullptr_t>));
C((!is_enum<int>::value));
C((!is_enum_v<float>));

// test is_union
C((is_union_v<test_union>));
C((!is_union<test_enum>::value));
C((!is_union_v<test_class>));
C((!is_union<void>::value));
C((!is_union_v<nullptr_t>));
C((!is_union<int>::value));
C((!is_union_v<float>));

// test is_class
C((is_class_v<test_class>));
C((!is_class<test_enum>::value));
C((!is_class_v<test_union>));
C((!is_class<void>::value));
C((!is_class_v<nullptr_t>));
C((!is_class<int>::value));
C((!is_class_v<float>));

// test is_function
C((is_function_v<int(int)>));
C((is_function<int(int, const char *, ...) const>::value));
C((is_function_v<int(int) volatile &>));
C((is_function<int(int) const volatile && noexcept>::value));
C((!is_function_v<int>));
C((!is_function<test_class>::value));
C((!is_function_v<decltype(test_lambda)>));
C((!is_function<int(*)(int)>::value));
C((!is_function_v<int(&)(int) noexcept>));
C((!is_function<void* test_class::*>::value));
C((!is_function_v<void* test_class::*&>));
C((!is_function<void* test_class::*&&>::value));
C((!is_function_v<void(test_class::*)()>));
C((!is_function<void(test_class::*&)()>::value));
C((!is_function_v<void(test_class::*&&)()>));

// test is_pointer
C((is_pointer_v<void*>));
C((is_pointer<void**>::value));
C((is_pointer_v<test_class*>));
C((is_pointer<const test_class*>::value));
C((is_pointer_v<void(*)()>));
C((!is_pointer<void>::value));
C((!is_pointer_v<nullptr_t>));
C((!is_pointer<test_class>::value));
C((!is_pointer_v<const test_class&>));
C((!is_pointer<test_class&&>::value));
C((!is_pointer_v<test_enum[10]>));
C((!is_pointer<void()>::value));
C((!is_pointer_v<void* test_class::*>));
C((!is_pointer<void(test_class::*)()>::value));

// test is_lvalue_reference
C((is_lvalue_reference_v<void*&>));
C((is_lvalue_reference<nullptr_t&>::value));
C((is_lvalue_reference_v<test_class&>));
C((is_lvalue_reference<const test_class&>::value));
C((is_lvalue_reference_v<test_enum(&)[10]>));
C((is_lvalue_reference<void(&)()>::value));
C((is_lvalue_reference_v<void(*&)()>));
C((is_lvalue_reference<void* test_class::*&>::value));
C((is_lvalue_reference_v<void(test_class::*&)()>));
C((!is_lvalue_reference<void>::value));
C((!is_lvalue_reference_v<void*&&>));
C((!is_lvalue_reference<nullptr_t&&>::value));
C((!is_lvalue_reference_v<test_class>));
C((!is_lvalue_reference<const test_class*>::value));
C((!is_lvalue_reference_v<test_class&&>));
C((!is_lvalue_reference<test_enum[10]>::value));
C((!is_lvalue_reference_v<void()>));
C((!is_lvalue_reference<void* test_class::*>::value));
C((!is_lvalue_reference_v<void* test_class::*&&>));
C((!is_lvalue_reference<void(test_class::*)()>::value));
C((!is_lvalue_reference_v<void(test_class::*&&)()>));

// test is_rvalue_reference
C((is_rvalue_reference_v<void*&&>));
C((is_rvalue_reference<nullptr_t&&>::value));
C((is_rvalue_reference_v<test_class&&>));
C((is_rvalue_reference<const test_class&&>::value));
C((is_rvalue_reference_v<test_enum(&&)[10]>));
C((is_rvalue_reference<void(&&)()>::value));
C((is_rvalue_reference_v<void(*&&)()>));
C((is_rvalue_reference<void* test_class::*&&>::value));
C((is_rvalue_reference_v<void(test_class::*&&)()>));
C((!is_rvalue_reference<void>::value));
C((!is_rvalue_reference_v<void*&>));
C((!is_rvalue_reference<nullptr_t&>::value));
C((!is_rvalue_reference_v<test_class>));
C((!is_rvalue_reference<const test_class*>::value));
C((!is_rvalue_reference_v<test_class&>));
C((!is_rvalue_reference<test_enum[10]>::value));
C((!is_rvalue_reference_v<void()>));
C((!is_rvalue_reference<void* test_class::*>::value));
C((!is_rvalue_reference_v<void* test_class::*&>));
C((!is_rvalue_reference<void(test_class::*)()>::value));
C((!is_rvalue_reference_v<void(test_class::*&)()>));

// test is_member_object_pointer
C((is_member_object_pointer_v<int test_class::*>));
C((!is_member_object_pointer<void*>::value));
C((!is_member_object_pointer_v<nullptr_t>));
C((!is_member_object_pointer<void(int)>::value));
C((!is_member_object_pointer_v<void(*)(int)>));
C((!is_member_object_pointer<int test_class::*()>::value));
C((!is_member_object_pointer_v<int test_class::*&>));
C((!is_member_object_pointer<int(test_class::*&)()>::value));

// test is_member_function_pointer
C((is_member_function_pointer_v<int(test_class::*)()>));
C((!is_member_function_pointer<void*>::value));
C((!is_member_function_pointer_v<nullptr_t>));
C((!is_member_function_pointer<void(int)>::value));
C((!is_member_function_pointer_v<void(*)(int)>));
C((!is_member_function_pointer<int test_class::*>::value));
C((!is_member_function_pointer_v<int test_class::*&>));
C((!is_member_function_pointer<int(test_class::*&)()>::value));

//------------------------------------------------------------------------------
// composite type categories
//------------------------------------------------------------------------------

// test is_fundamental
C((is_fundamental_v<void>));
C((is_fundamental<nullptr_t>::value));
C((is_fundamental_v<bool>));
C((is_fundamental<int const>::value));
C((is_fundamental_v<float volatile>));
C((is_fundamental<double const volatile>::value));
C((!is_fundamental_v<integral_constant<int, 0>>));
C((!is_fundamental<double() const>::value));

// test is_arithmetic
C((is_arithmetic_v<bool>));
C((is_arithmetic<int const>::value));
C((is_arithmetic_v<float volatile>));
C((is_arithmetic<double const volatile>::value));
C((!is_arithmetic_v<void>));
C((!is_arithmetic<nullptr_t>::value));
C((!is_arithmetic_v<integral_constant<int, 0>>));
C((!is_arithmetic<double() const>::value));

// test is_scalar
namespace test_is_scalar {
    static __attribute__((unused)) struct S { int m; } s;
    static __attribute__((unused)) int S::* mp = &S::m;
    enum class E { e };
    C((is_scalar_v<int>));
    C((is_scalar_v<double>));
    C((is_scalar_v<E>));
    C((is_scalar_v<char const*>));
    C((is_scalar_v<int S::*>));
    C((is_scalar_v<nullptr_t>));
    C((!is_scalar_v<S>));
}

// test is_object
C((!is_object_v<void>));
C(( is_object_v<int>));
C((!is_object_v<int&>));
C(( is_object_v<int*>));
C((!is_object_v<int*&>));
C(( is_object_v<test_class>));
C((!is_object_v<test_class&>));
C(( is_object_v<test_class*>));
C((!is_object_v<int()>));
C(( is_object_v<int(*)()>));
C((!is_object_v<int(&)()>));

// test is_compound
namespace test_is_compound {
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunneeded-internal-declaration"
    static void f();
    #pragma GCC diagnostic pop
    class Z {};
    union U {};
    enum struct E { e };
    struct S {
        int i : 8;
        int j;
        void foo();
    };
    C((!is_compound_v<int>));
    C((is_compound_v<int*>));
    C((is_compound_v<int&>));
    C((is_compound_v<decltype(f)>));
    C((is_compound_v<decltype(&f)>));
    C((is_compound_v<char[10]>));
    C((is_compound_v<Z>));
    C((is_compound_v<U>));
    C((is_compound_v<E>));
    C((is_compound_v<decltype(E::e)>));
    C((!is_compound_v<decltype(S::i)>));
    C((!is_compound_v<decltype(S::j)>));
    C((is_compound_v<decltype(&S::j)>));
    C((is_compound_v<decltype(&S::foo)>));
}

// test is_reference
C((is_reference_v<void*&>));
C((is_reference<void*&&>::value));
C((is_reference_v<nullptr_t&>));
C((is_reference<nullptr_t&&>::value));
C((is_reference_v<test_class&>));
C((is_reference<test_class&&>::value));
C((is_reference_v<const test_class&&>));
C((is_reference<test_enum(&)[10]>::value));
C((is_reference_v<test_enum(&&)[10]>));
C((is_reference<void(&&)()>::value));
C((is_reference_v<void(*&&)()>));
C((is_reference<void* test_class::*&>::value));
C((is_reference_v<void* test_class::*&&>));
C((is_reference<void(test_class::*&)()>::value));
C((is_reference_v<void(test_class::*&&)()>));
C((!is_reference<void>::value));
C((!is_reference_v<test_class>));
C((!is_reference<const test_class*>::value));
C((!is_reference_v<test_enum[10]>));
C((!is_reference<void()>::value));
C((!is_reference_v<void* test_class::*>));
C((!is_reference<void(test_class::*)()>::value));

// test is_member_pointer
C((is_member_pointer_v<int test_class::*>));
C((is_member_pointer<int(test_class::*)()>::value));
C((!is_member_pointer_v<void*>));
C((!is_member_pointer<nullptr_t>::value));
C((!is_member_pointer_v<void(int)>));
C((!is_member_pointer<void(*)(int)>::value));
C((!is_member_pointer_v<int test_class::*&>));
C((!is_member_pointer<int(test_class::*&)()>::value));

//------------------------------------------------------------------------------
// type properties
//------------------------------------------------------------------------------

// test is_const
C((is_const_v<void const>));
C((is_const<void* const>::value));
C((!is_const_v<void>));
C((!is_const<void volatile>::value));
C((!is_const_v<void() const>));

// test is_volatile
C((is_volatile_v<void volatile>));
C((is_volatile<void* volatile>::value));
C((!is_volatile_v<void>));
C((!is_volatile<void const>::value));
C((!is_volatile_v<void() volatile>));

// test is_trivial
namespace test_is_trivial {
    struct A { int m; };
    struct B { B() {} };
    class Z {
        private:
        Z() = default;
    };
    C((is_trivial_v<A>));
    C((!is_trivial_v<B>));
    C((is_trivial_v<Z>));
}

// test is_trivially_copyable
namespace is_trivially_copyable {
    struct A { int m; };
    struct B { B(B const&) {} };
    struct Z { virtual void foo(); };
    struct D {
        int m;
        D(D const&) = default;
        D(int x) : m(x + 1) {}
    };
    C((is_trivially_copyable_v<A>));
    C((!is_trivially_copyable_v<B>));
    C((!is_trivially_copyable_v<Z>));
    C((is_trivially_copyable_v<D>));
}

// test is_standard_layout
namespace is_standard_layout {
    struct A { int m; };
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-private-field"
    class B: public A { int m; };
    #pragma GCC diagnostic pop
    struct Z { virtual void foo(); };
    C((!is_standard_layout_v<B>));
    C((is_standard_layout_v<A>));
    C((!is_standard_layout_v<Z>));
}

// test is_pod
namespace test_is_pod {
    struct A { int m; };
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-private-field"
    class B: public A { int m; };
    #pragma GCC diagnostic pop
    struct Z { virtual void foo(); };
    C((is_pod_v<A>));
    C((!is_pod_v<B>));
    C((!is_pod_v<Z>));
}

// test is_literal_type
namespace test_is_literal_type {
    struct A { int m; };
    struct B { virtual ~B(); };
    C((is_literal_type_v<A>));
    C((!is_literal_type_v<B>));
}

// test has_unique_object_representations
/** @todo */

// test is_empty
namespace test_is_empty {
    struct A {};
    struct B { int m; };
    struct Z { static __attribute__((unused)) int m; };
    struct D { virtual ~D(); };
    union E {};
    struct F { [[no_unique_address]] E e; };
    struct G {
        int : 0;
    };
    C((is_empty_v<A>));
    C((!is_empty_v<B>));
    C((is_empty_v<Z>));
    C((!is_empty_v<D>));
    C((!is_empty_v<E>));
    C((is_empty_v<G>));
}

// test is_polymorphic
namespace test_is_polymorphic {
    struct A { int m; };
    struct B { virtual void foo(); };
    struct Z: B {};
    struct D { virtual ~D() = default; };
    struct E : A {};
    struct F : virtual A {};
    struct AX : A {};
    struct AY : A {};
    struct XY : virtual AX, virtual AY {};
    C((!is_polymorphic_v<A>));
    C((is_polymorphic_v<B>));
    C((is_polymorphic_v<Z>));
    C((is_polymorphic_v<D>));
    C((!is_polymorphic_v<E>));
    C((!is_polymorphic_v<F>));
    C((!is_polymorphic_v<XY>));
}

// test is_abstract
namespace test_is_abstract {
    struct A { int m; };
    struct B { virtual void foo(); };
    struct Z{ virtual void foo() = 0; };
    struct D : Z{};
    C((!is_abstract_v<A>));
    C((!is_abstract_v<B>));
    C((is_abstract_v<Z>));
    C((is_abstract_v<D>));
}

// test is_final
namespace test_is_final {
    class A {};
    class B final {};
    union U final {
        int x;
        double d;
    };
    C((!is_final_v<A>));
    C((is_final_v<B>));
    C((is_final_v<U>));
}

// test is_aggregate
/** @todo get more complicated tests */
namespace test_is_aggregate {
    struct A { int x, y; };
    C((!is_aggregate_v<int>));
    C((is_aggregate_v<A>));
}

// test is_signed
C((!is_signed_v<void>));
C((!is_signed_v<void*>));
C(( is_signed_v<int>));
C((!is_signed_v<int*>));
C((!is_signed_v<unsigned int>));
C((!is_signed_v<unsigned int*>));
C(( is_signed_v<float>));
C(( is_signed_v<double>));
C(( is_signed_v<  signed __int48>));
C((!is_signed_v<unsigned __int48>));
C((!is_signed_v<bool>));

// test is_unsigned
C((!is_unsigned_v<void>));
C((!is_unsigned_v<void*>));
C((!is_unsigned_v<int>));
C((!is_unsigned_v<int*>));
C(( is_unsigned_v<unsigned int>));
C((!is_unsigned_v<unsigned int*>));
C((!is_unsigned_v<float>));
C((!is_unsigned_v<double>));
C((!is_unsigned_v<  signed __int48>));
C(( is_unsigned_v<unsigned __int48>));
C(( is_unsigned_v<bool>));

//------------------------------------------------------------------------------
// const/volatile addition traits
//------------------------------------------------------------------------------

// test add_const
C((is_same_v<void const, add_const_t<void>>));
C((is_same_v<void const, add_const<void const>::type>));
C((is_same_v<void() volatile, add_const_t<void() volatile>>));

// test add_volatile
C((is_same_v<void volatile, add_volatile_t<void>>));
C((is_same_v<void volatile, add_volatile<void volatile>::type>));
C((is_same_v<void() const, add_volatile_t<void() const>>));

// test add_cv
C((is_same_v<void const volatile, add_cv_t<void>>));
C((is_same_v<void const volatile, add_cv<void const>::type>));
C((is_same_v<void const volatile, add_cv_t<void volatile>>));
C((is_same_v<void const volatile, add_cv<void const volatile>::type>));
C((is_same_v<void() const volatile, add_cv_t<void() const volatile>>));

//------------------------------------------------------------------------------
// reference/pointer transformation traits
//------------------------------------------------------------------------------

// test remove_pointer
C((is_same_v<int const, remove_pointer_t<int const>>));
C((is_same_v<int() const volatile, remove_pointer<int() const volatile>::type>));
C((is_same_v<void, remove_pointer_t<void*>>));
C((is_same_v<void*, remove_pointer<void** const>::type>));
C((is_same_v<void(), remove_pointer_t<void(* volatile)()>>));
C((is_same_v<void(*)(), remove_pointer<void(** const volatile)()>::type>));
C((is_same_v<void*&, remove_pointer_t<void*&>>));
C((is_same_v<void(*&)(), remove_pointer<void(*&)()>::type>));

// test remove_reference
C((is_same_v<int const, remove_reference_t<int const>>));
C((is_same_v<int() const volatile, remove_reference<int() const volatile>::type>));
C((is_same_v<int, remove_reference_t<int&>>));
C((is_same_v<void(), remove_reference<void(&)()>::type>));
C((is_same_v<void*, remove_reference_t<void*&>>));
C((is_same_v<void(*)(), remove_reference<void(*&)()>::type>));
C((is_same_v<void*, remove_reference_t<void*>>));
C((is_same_v<void**, remove_reference<void**>::type>));
C((is_same_v<void(*)(), remove_reference_t<void(*)()>>));
C((is_same_v<void(**)(), remove_reference<void(**)()>::type>));

// test remove_cvref
C((is_same_v<remove_cvref_t<int>, int>));
C((is_same_v<remove_cvref_t<int&>, int>));
C((is_same_v<remove_cvref_t<int&&>, int>));
C((is_same_v<remove_cvref_t<const int&>, int>));
C((is_same_v<remove_cvref_t<const int[2]>, int[2]>));
C((is_same_v<remove_cvref_t<const int(&)[2]>, int[2]>));
C((is_same_v<remove_cvref_t<int(int)>, int(int)>));

// test add_pointer
C((is_same_v<int const*, add_pointer_t<int const>>));
C((is_same_v<int() const volatile, add_pointer<int() const volatile>::type>));
C((is_same_v<void*, add_pointer_t<void>>));
C((is_same_v<void* const*, add_pointer<void* const>::type>));
C((is_same_v<void(* volatile*)(), add_pointer_t<void(* volatile)()>>));
C((is_same_v<void(* const* volatile*)(), add_pointer<void(* const* volatile)()>::type>));
C((is_same_v<void*&, add_pointer_t<void*&>>));
C((is_same_v<void(*&)(), add_pointer<void(*&)()>::type>));

// test add_lvalue_reference
C((is_same_v<int const&, add_lvalue_reference_t<int const>>));
C((is_same_v<int() const volatile, add_lvalue_reference<int() const volatile>::type>));
C((is_same_v<void, add_lvalue_reference_t<void>>));
C((is_same_v<void* const&, add_lvalue_reference<void* const>::type>));
C((is_same_v<void(* volatile&)(), add_lvalue_reference_t<void(* volatile)()>>));
C((is_same_v<void(* const* volatile&)(), add_lvalue_reference<void(* const* volatile)()>::type>));
C((is_same_v<void*&, add_lvalue_reference_t<void*&>>));
C((is_same_v<void(*&)(), add_lvalue_reference<void(*&)()>::type>));
C((is_same_v<void*&, add_lvalue_reference_t<void*&&>>));
C((is_same_v<void(*&)(), add_lvalue_reference<void(*&&)()>::type>));

// test add_rvalue_reference
C((is_same_v<int const&&, add_rvalue_reference_t<int const>>));
C((is_same_v<int() const volatile, add_rvalue_reference<int() const volatile>::type>));
C((is_same_v<void, add_rvalue_reference_t<void>>));
C((is_same_v<void* const&&, add_rvalue_reference<void* const>::type>));
C((is_same_v<void(* volatile&&)(), add_rvalue_reference_t<void(* volatile)()>>));
C((is_same_v<void(* const* volatile&&)(), add_rvalue_reference<void(* const* volatile)()>::type>));
C((is_same_v<void*&, add_rvalue_reference_t<void*&>>));
C((is_same_v<void(*&)(), add_rvalue_reference<void(*&)()>::type>));
C((is_same_v<void*&&, add_rvalue_reference_t<void*&&>>));
C((is_same_v<void(*&&)(), add_rvalue_reference<void(*&&)()>::type>));

//------------------------------------------------------------------------------
// alignment_of 
//------------------------------------------------------------------------------

// test alignment_of
/** @todo */

//------------------------------------------------------------------------------
// rank/extent
//------------------------------------------------------------------------------

// test rank
C((rank<int>{} == 0));
C((rank<int[5]>{} == 1));
C((rank<int[5][5]>{} == 2));
C((rank<int[][5][5]>{} == 3));

// test extent
C((extent_v<int[3]> == 3));
C((extent_v<int[3], 0> == 3));
C((extent_v<int[3][4], 0> == 3));
C((extent_v<int[3][4], 1> == 4));
C((extent_v<int[3][4], 2> == 0));
C((extent_v<int[]> == 0));

// test remove_extent
/** @todo */

// test remove_all_extents
/** @todo */

//------------------------------------------------------------------------------
// decay
//------------------------------------------------------------------------------

// test decay
C(( is_same_v<decay_t<int       >, int        >));
C((!is_same_v<decay_t<int       >, float      >));
C(( is_same_v<decay_t<int&      >, int        >));
C(( is_same_v<decay_t<int&&     >, int        >));
C(( is_same_v<decay_t<const int&>, int        >));
C(( is_same_v<decay_t<int[2]    >, int*       >));
C((!is_same_v<decay_t<int[4][2] >, int*       >));
C((!is_same_v<decay_t<int[4][2] >, int**      >));
C(( is_same_v<decay_t<int[4][2] >, int(*)[2]  >));
C(( is_same_v<decay_t<int(int)  >, int(*)(int)>));

//------------------------------------------------------------------------------
// underlying_type
//------------------------------------------------------------------------------

// test underlying_type
namespace test_underlying_type {
    enum e1 {};
    enum class e2 {};
    enum class e3 : unsigned {};
    enum class e4 : int {};
    C((!is_same_v<underlying_type_t<e1>, int>));
    C((is_same_v<underlying_type_t<e2>, int>));
    C((!is_same_v<underlying_type_t<e3>, int>));
    C((is_same_v<underlying_type_t<e4>, int>));
}

//------------------------------------------------------------------------------
// member classification traits
//------------------------------------------------------------------------------

// test is_constructible
C((is_constructible_v<int>));
C((is_constructible<int, int>::value));
C((is_constructible_v<int, int const&>));
C((is_constructible<int, int&&>::value));
C((is_constructible_v<int, float>));
C((is_constructible<test_enum, int>::value));
C((is_constructible_v<int, test_enum>));
C((!is_constructible<int, int, int>::value));
C((!is_constructible_v<int()>));
C((!is_constructible<int, test_class>::value));
C((!is_constructible_v<test_class, int>));

// test is_trivially_constructible
C((is_trivially_constructible_v<int>));
C((is_trivially_constructible<int, int const&>::value));
C((is_trivially_constructible_v<int, int&&>));
C((!is_trivially_constructible<test_class>::value));
C((!is_trivially_constructible_v<test_union>));
C((!is_trivially_constructible<int()>::value));

// test is_nothrow_constructible
C((is_nothrow_constructible_v<int>));
C((is_nothrow_constructible<int, int const&>::value));
C((is_nothrow_constructible_v<int, int&&>));
C((is_nothrow_constructible<test_class>::value));
C((!is_nothrow_constructible_v<test_union>));
C((!is_nothrow_constructible<int()>::value));

// test is_default_constructible
C((is_default_constructible_v<int>));
C((is_default_constructible<test_enum>::value));
C((is_default_constructible_v<int>));
C((is_default_constructible<test_class>::value));
C((!is_default_constructible_v<int()>));

// test is_trivially_default_constructible
C((is_trivially_default_constructible_v<int>));
C((!is_trivially_default_constructible<test_class>::value));
C((!is_trivially_default_constructible_v<test_union>));
C((!is_trivially_default_constructible<int()>::value));

// test is_nothrow_default_constructible
C((is_nothrow_default_constructible_v<int>));
C((is_nothrow_default_constructible<test_class>::value));
C((!is_nothrow_default_constructible_v<test_union>));
C((!is_nothrow_default_constructible<int()>::value));

// test is_copy_constructible
C((is_copy_constructible_v<int>));
C((is_copy_constructible<test_enum>::value));
C((is_copy_constructible_v<int>));
C((is_copy_constructible<test_class>::value));
C((!is_copy_constructible_v<int()>));

// test is_trivially_copy_constructible
C((is_trivially_copy_constructible_v<int>));
C((!is_trivially_copy_constructible<test_class>::value));
C((is_trivially_copy_constructible_v<test_union>));
C((!is_trivially_copy_constructible<int()>::value));

// test is_nothrow_copy_constructible
C((is_nothrow_copy_constructible_v<int>));
C((is_nothrow_copy_constructible<test_class>::value));
C((is_nothrow_copy_constructible_v<test_union>));
C((!is_nothrow_copy_constructible<int()>::value));

// test is_move_constructible
C((is_move_constructible_v<int>));
C((is_move_constructible<test_enum>::value));
C((is_move_constructible_v<int>));
C((is_move_constructible<test_class>::value));
C((!is_move_constructible_v<int()>));

// test is_trivially_move_constructible
C((is_trivially_move_constructible_v<int>));
C((is_trivially_move_constructible<test_union>::value));
C((!is_trivially_move_constructible_v<test_class>));
C((!is_trivially_move_constructible<int()>::value));

// test is_nothrow_move_constructible
C((is_nothrow_move_constructible_v<int>));
C((is_nothrow_move_constructible<test_class>::value));
C((is_nothrow_move_constructible_v<test_union>));
C((!is_nothrow_move_constructible<int()>::value));

// test is_assignable
/** @todo get more complicated tests */
C((!is_assignable_v<int, int>));
C((is_assignable_v<int&, int>));
C((!is_assignable_v<int, double>));

// test is_trivially_assignable
/** @todo get more complicated tests */
C((is_trivially_assignable_v<test_struct&, const test_struct&>));

// test is_nothrow_assignable
/** @todo get more complicated tests */
C((is_nothrow_assignable_v<int&, double>));

// test is_copy_assignable
/** @todo get more complicated tests */
C((is_copy_assignable_v<test_struct>));
C((!is_copy_assignable_v<int[2]>));

// test is_nothrow_copy_assignable
/** @todo get more complicated tests */
C((is_nothrow_copy_assignable_v<int>));

// test is_move_assignable
/** @todo get more complicated tests */
namespace test_is_move_assignable {
    struct NoMove {
        NoMove& operator=(const NoMove&) { return *this; }
    };
    C((is_move_assignable_v<test_struct>));
    C((!is_move_assignable_v<int[2]>));
    C((is_move_assignable_v<NoMove>));
}

// test is_nothrow_move_assignable
/** @todo get more complicated tests */
namespace test_is_nothrow_move_assignable {
    struct NoMove {
        NoMove& operator=(const NoMove&) { return *this; }
    };
    C((!is_nothrow_move_assignable_v<NoMove>));
}

/* Clang 16.0.0 required */
#if 0
// test is_destructible
/** @todo */
#endif

// test is_trivially_destructible
/** @todo get more complicated tests */
namespace test_is_trivially_destructible {
    struct Bar {
        ~Bar() = default;
    };
    C((is_trivially_destructible<Bar>{} == true));
}

/* Clang 16.0.0 required */
#if 0
// test is_nothrow_destructible
/** @todo */
#endif

// test has_virtual_destructor
namespace test_has_virtual_destructor {
    struct S {};
    struct B { virtual ~B() {} };
    struct D : B { ~D() {} };
    C((!has_virtual_destructor_v<S>));
    C((has_virtual_destructor_v<B>));
    C((has_virtual_destructor_v<D>));
}

//------------------------------------------------------------------------------
// swappable classification traits
//------------------------------------------------------------------------------

// test is_swappable_with
/** @todo */

// test is_swappable
/** @todo */

// test is_nothrow_swappable_with
/** @todo */

// test is_nothrow_swappable
/** @todo */

#undef C

} // namespace

} // namespace std
