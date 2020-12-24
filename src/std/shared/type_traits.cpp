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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunneeded-internal-declaration"
const auto test_lambda = [](){};
#pragma GCC diagnostic pop

// test type_identity
template<class T> void test_type_identity(integral_constant<T, 0>, type_identity_t<T>);
C((is_void_v<decltype(test_type_identity(bool_constant<false>{}, 0))>));

// test is_same
C((is_same_v<void, void>));
C((!is_same<void, void const>::value));
C((!is_same_v<void const, void() const>));

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

// test is_arithmetic
C((is_arithmetic_v<bool>));
C((is_arithmetic<int const>::value));
C((is_arithmetic_v<float volatile>));
C((is_arithmetic<double const volatile>::value));
C((!is_arithmetic_v<void>));
C((!is_arithmetic<nullptr_t>::value));
C((!is_arithmetic_v<integral_constant<int, 0>>));
C((!is_arithmetic<double() const>::value));

// test is_fundamental
C((is_fundamental_v<void>));
C((is_fundamental<nullptr_t>::value));
C((is_fundamental_v<bool>));
C((is_fundamental<int const>::value));
C((is_fundamental_v<float volatile>));
C((is_fundamental<double const volatile>::value));
C((!is_fundamental_v<integral_constant<int, 0>>));
C((!is_fundamental<double() const>::value));

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

// test is_member_pointer
C((is_member_pointer_v<int test_class::*>));
C((is_member_pointer<int(test_class::*)()>::value));
C((!is_member_pointer_v<void*>));
C((!is_member_pointer<nullptr_t>::value));
C((!is_member_pointer_v<void(int)>));
C((!is_member_pointer<void(*)(int)>::value));
C((!is_member_pointer_v<int test_class::*&>));
C((!is_member_pointer<int(test_class::*&)()>::value));

// test is_member_function_pointer
C((is_member_function_pointer_v<int(test_class::*)()>));
C((!is_member_function_pointer<void*>::value));
C((!is_member_function_pointer_v<nullptr_t>));
C((!is_member_function_pointer<void(int)>::value));
C((!is_member_function_pointer_v<void(*)(int)>));
C((!is_member_function_pointer<int test_class::*>::value));
C((!is_member_function_pointer_v<int test_class::*&>));
C((!is_member_function_pointer<int(test_class::*&)()>::value));

// test is_member_object_pointer
C((is_member_object_pointer_v<int test_class::*>));
C((!is_member_object_pointer<void*>::value));
C((!is_member_object_pointer_v<nullptr_t>));
C((!is_member_object_pointer<void(int)>::value));
C((!is_member_object_pointer_v<void(*)(int)>));
C((!is_member_object_pointer<int test_class::*()>::value));
C((!is_member_object_pointer_v<int test_class::*&>));
C((!is_member_object_pointer<int(test_class::*&)()>::value));

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

#undef C

} // namespace

} // namespace std
