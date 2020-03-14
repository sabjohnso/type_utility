#pragma once
//
// ... Type Utility header files
//
#include <type_utility/config.hpp>
#include <type_utility/import.hpp>

namespace TypeUtility::Core {

  /**
   * @brief Type proxy class
   */
  template<typename T>
  struct Type
  {
  public:
    using type = T;

    /**
     * @brief Make an instance of the refered type
     */
    template<typename... Ts>
    static constexpr type
    make(Ts&&... xs)
    {
      return type(forward<Ts>(xs)...);
    }

    /**
     * @brief Make an instance of the refered type as function call
     */
    template<typename... Ts>
    constexpr type
    operator()(Ts&&... xs) const&
    {
      return make(forward<Ts>(xs)...);
    }

    /**
     * @brief Return the size in bytes of the refered type
     */
    static constexpr size_t
    size()
    {
      return sizeof(type);
    }

    /**
     * @brief Return false as the default for equality comparison
     */
    template<typename U>
    constexpr bool operator==(U) const&
    {
      return false;
    }

    /**
     * @brief Return true for equality comparsion with a proxy to the same type
     */
    constexpr bool operator==(Type) const& { return true; }

    /**
     * @brief Return the logical negation of equality comparison
     */
    template<typename U>
    constexpr bool
    operator!=(U&& other) const&
    {
      return !(*this == forward<U>(other));
    }

    /**
     * @brief checks if a type is void
     */
    static constexpr bool
    isvoid()
    {
      return is_void<type>::value;
    }

    /**
     * @brief checks if a type is std::nullptr_t
     */
    static constexpr bool
    isnull_pointer()
    {
      return is_null_pointer<type>::value;
    }

    /**
     * @brief checks if a type is integral type
     */
    static constexpr bool
    isintegral()
    {
      return is_integral<type>::value;
    }

    /**
     * @brief checks if a type is floating-point type
     */
    static constexpr bool
    isfloating_point()
    {
      return is_floating_point<type>::value;
    }

    /**
     * @brief checks if a type is an array type
     */
    static constexpr bool
    isarray()
    {
      return is_array<type>::value;
    }

    /**
     * @brief checks if a type is an enumeration type
     */
    static constexpr bool
    isenum()
    {
      return is_enum<type>::value;
    }

    /**
     * @brief checks if a type is an union type
     */
    static constexpr bool
    isunion()
    {
      return is_union<type>::value;
    }

    /**
     * @brief checks if a type is a non-union class type
     */
    static constexpr bool
    isclass()
    {
      return is_class<type>::value;
    }

    /**
     * @brief checks if a type is a function type
     */
    static constexpr bool
    isfunction()
    {
      return is_function<type>::value;
    }

    /**
     * @brief checks if a type is a pointer type
     */
    static constexpr bool
    ispointer()
    {
      return is_pointer<type>::value;
    }

    /**
     * @brief checks if a type is lvalue reference
     */
    static constexpr bool
    islvalue_reference()
    {
      return is_lvalue_reference<type>::value;
    }

    /**
     * @brief checks if a type is rvalue reference
     */
    static constexpr bool
    isrvalue_reference()
    {
      return is_rvalue_reference<type>::value;
    }

    /** checks if a type is a pointer to a non-static member object
     */
    static constexpr bool
    ismember_object_pointer()
    {
      return is_member_object_pointer<type>::value;
    }

    /**
     * @brief checks if a type is a pointer to a non-static member function
     */
    static constexpr bool
    ismember_function_pointer()
    {
      return is_member_function_pointer<type>::value;
    }

    /**
     * @brief checks if a type is fundamental type
     */
    static constexpr bool
    isfundamental()
    {
      return is_fundamental<type>{};
    }

    /**
     * @brief checks if a type is arithmetic type
     */
    static constexpr bool
    isarithmetic()
    {
      return is_arithmetic<type>{};
    }

    /**
     * @brief checks if a type is scalar type
     */
    static constexpr bool
    isscalar()
    {
      return is_scalar<type>{};
    }

    /**
     * @brief checks if a type is object type
     */
    static constexpr bool
    isobject()
    {
      return is_object<type>{};
    }

    /**
     * @brief checks if a type is compound type
     */
    static constexpr bool
    iscompound()
    {
      return is_compound<type>{};
    }

    /**
     * @brief checks if a type is either lvalue reference or rvalue reference
     */
    static constexpr bool
    isreference()
    {
      return is_reference<type>{};
    }

    /**
     * @brief checks if a type is a pointer to a non-static member function or
     * object
     */
    static constexpr bool
    ismember_pointer()
    {
      return is_member_pointer<type>{};
    }

    /**
     * @brief checks if a type is const-qualified
     */
    static constexpr bool
    isconst()
    {
      return is_const<type>::value;
    }

    /**
     * @brief checks if a type is volatile-qualified
     */
    static constexpr bool
    isvolatile()
    {
      return is_volatile<type>::value;
    }

    /**
     * @brief checks if a type is trivial
     */
    static constexpr bool
    istrivial()
    {
      return is_trivial<type>::value;
    }

    /**
     * @brief checks if a type is trivially copyable
     */
    static constexpr bool
    istrivially_copyable()
    {
      return is_trivially_copyable<type>::value;
    }

    /**
     * @brief checks if a type is standard-layout type
     */
    static constexpr bool
    isstandard_layout()
    {
      return is_standard_layout<type>::value;
    }

    /**
     * @brief checks if a type is plain-old data (POD) type
     */
    static constexpr bool
    ispod()
    {
      return is_pod<type>::value;
    }

    /**
     * @brief checks if a type is literal type
     */
    static constexpr bool
    isliteral_type()
    {
      return is_literal_type<type>::value;
    }

    /**
     * @brief checks if every bit in the type's object representation
     * contributes to its value
     */
    static constexpr bool
    ha_unique_object_representations()
    {
      return has_unique_object_representations<type>::value;
    }

    /**
     * @brief checks if a type is class (but not union) type and has no data
     */
    static constexpr bool
    isempty()
    {
      return is_empty<type>::value;
    }

    /**
     * @brief checks if a type is polymorphic class type
     */
    static constexpr bool
    ispolymorphic()
    {
      return is_polymorphic<type>::value;
    }

    /**
     * @brief checks if a type is an abstract class type
     */
    static constexpr bool
    isabstract()
    {
      return is_abstract<type>::value;
    }

    /**
     * @brief checks if a type is a final class type
     */
    static constexpr bool
    isfinal()
    {
      return is_final<type>::value;
    }

    /**
     * @brief checks if a type is an aggregate type
     */
    static constexpr bool
    isaggregate()
    {
      return is_aggregate<type>::value;
    }

    /**
     * @brief checks if a type is signed arithmetic type
     */
    static constexpr bool
    issigned()
    {
      return is_signed<type>::value;
    }

    /**
     * @brief checks if a type is unsigned arithmetic type
     */
    static constexpr bool
    isunsigned()
    {
      return is_unsigned<type>::value;
    }

    /**
     * @brief checks if a type has a default constructor
     */
    template<typename... Us>
    static constexpr bool
    isconstructible()
    {
      return is_constructible<type, Us...>::value;
    }

    /**
     * @brief checks if a type has a default constructor
     */
    template<typename... Us>
    static constexpr bool
    istrivially_constructible()
    {
      return is_trivially_constructible<type, Us...>::value;
    }

    /**
     * @brief checks if a type has a default constructor
     */
    template<typename... Us>
    static constexpr bool
    isnothrow_constructible()
    {
      return is_nothrow_constructible<type, Us...>::value;
    }

    /**
     * @brief checks if a type has a default constructor
     */
    static constexpr bool
    isdefault_constructible()
    {
      return is_default_constructible<type>::value;
    }

    /**
     * @brief checks if a type has a default constructor
     */
    static constexpr bool
    istrivially_default_constructible()
    {
      return is_trivially_default_constructible<type>::value;
    }

    /**
     * @brief checks if a type has a default constructor
     */
    static constexpr bool
    isnothrow_default_constructible()
    {
      return is_nothrow_default_constructible<type>::value;
    }

    /**
     * @brief checks if a type has a copy constructor
     */
    static constexpr bool
    iscopy_constructible()
    {
      return is_copy_constructible<type>::value;
    }

    /**
     * @brief checks if a type has a copy constructor
     */
    static constexpr bool
    istrivially_copy_constructible()
    {
      return is_trivially_copy_constructible<type>::value;
    }

    /**
     * @brief checks if a type has a copy constructor
     */
    static constexpr bool
    isnothrow_copy_constructible()
    {
      return is_nothrow_copy_constructible<type>::value;
    }

    /**
     * @brief checks if a type can be constructed from an rvalue reference
     */
    static constexpr bool
    ismove_constructible()
    {
      return is_move_constructible<type>::value;
    }

    /**
     * @brief checks if a type can be constructed from an rvalue reference
     */
    static constexpr bool
    istrivially_move_constructible()
    {
      return is_trivially_move_constructible<type>::value;
    }

    /**
     * @brief checks if a type can be constructed from an rvalue reference
     */
    static constexpr bool
    isnothrow_move_constructible()
    {
      return is_nothrow_move_constructible<type>::value;
    }

    /**
     * @brief checks if a type has a assignment operator for a specific argument
     */
    template<typename U>
    static constexpr bool
    isassignable()
    {
      return is_assignable<type, U>::value;
    }

    /** checks if a type has a assignment operator for a specific argument
     */
    template<typename U>
    static constexpr bool
    istrivially_assignable()
    {
      return is_trivially_assignable<type, U>::value;
    }

    /**
     * @brief checks if a type has a assignment operator for a specific argument
     */
    template<typename U>
    static constexpr bool
    isnothrow_assignable()
    {
      return is_nothrow_assignable<type, U>::value;
    }

    /**
     * @brief checks if a type has a copy assignment operator
     */
    static constexpr bool
    iscopy_assignable()
    {
      return is_copy_assignable<type>::value;
    }

    /**
     * @brief checks if a type has a copy assignment operator
     */
    static constexpr bool
    istrivially_copy_assignable()
    {
      return is_trivially_copy_assignable<type>::value;
    }

    /**
     * @brief checks if a type has a copy assignment operator
     */
    static constexpr bool
    isnothrow_copy_assignable()
    {
      return is_nothrow_copy_assignable<type>::value;
    }

    /**
     * @brief checks if a type has a move assignment operator
     */
    static constexpr bool
    ismove_assignable()
    {
      return is_move_assignable<type>::value;
    }

    /**
     * @brief checks if a type has a move assignment operator
     */
    static constexpr bool
    istrivially_move_assignable()
    {
      return is_trivially_move_assignable<type>::value;
    }

    /**
     * @brief checks if a type has a move assignment operator
     */
    static constexpr bool
    isnothrow_move_assignable()
    {
      return is_nothrow_move_assignable<type>::value;
    }

    /**
     * @brief checks if a type has a non-deleted destructor
     */
    static constexpr bool
    isdestructible()
    {
      return is_destructible<type>::value;
    }

    /**
     * @brief checks if a type has a non-deleted destructor
     */
    static constexpr bool
    istrivially_destructible()
    {
      return is_trivially_destructible<type>::value;
    }

    /**
     * @brief checks if a type has a non-deleted destructor
     */
    static constexpr bool
    isnothrow_destructible()
    {
      return is_nothrow_destructible<type>::value;
    }

    /**
     * @brief checks if a type has a virtual destructor
     */
    static constexpr bool
    hasvirtual_destructor()
    {
      return has_virtual_destructor<type>::value;
    }

    /**
     * @brief checks if objects of a type can be swapped with objects of same or
     * different type
     */
    template<typename U>
    static constexpr bool
    isswappable_with()
    {
      return is_swappable_with<type, U>::value;
    }

    /**
     * @brief checks if objects of a type can be swapped with objects of same or
     * different type
     */
    static constexpr bool
    isswappable()
    {
      return is_swappable<type>::value;
    }

    /**
     * @brief checks if objects of a type can be swapped with objects of same or
     * different type
     */
    template<typename U>
    static constexpr bool
    isnothrow_swappable_with()
    {
      return is_nothrow_swappable_with<type, U>::value;
    }

    /**
     * @brief checks if objects of a type can be swapped with objects of same or
     * different type
     */
    static constexpr bool
    isnothrow_swappable()
    {
      return is_nothrow_swappable<type>::value;
    }

    /**
     * @brief checks if a type can be invoked (as if by std::invoke) with the
     * given argument types
     */
    template<typename... Ts>
    static constexpr bool
    isinvocable()
    {
      return is_invocable<T, Ts...>::value;
    }

    /**
     * @brief checks if a type can be invoked (as if by std::invoke) with the
     * given argument types to return a type convertible to R
     */
    template<typename R, typename... Ts>
    static constexpr bool
    isinvocable_r()
    {
      return is_invocable_r<R, T, Ts...>::value;
    }

    /**
     * @brief checks if a type can be invoked (as if by std::invoke) with the
     * given argument types
     */
    template<typename... Ts>
    static constexpr bool
    isnothrow_invocable()
    {
      return is_nothrow_invocable<T, Ts...>::value;
    }

    /**
     * @brief checks if a type can be invoked (as if by std::invoke) with the
     * given argument types to return a type convertible to R
     */
    template<typename R, typename... Ts>
    static constexpr bool
    isnothrow_invocable_r()
    {
      return is_nothrow_invocable_r<T, Ts...>::value;
    }

  }; // end of class type

  /**
   * @brief Proxy type value template
   */
  template<typename T>
  constexpr Type<T> type{};

  /**
   * @brief Inject a printed representation of a type into an output stream
   *
   * @details Use of this operator requires RTTI and might not be suitable for
   * all applications
   */
  template<typename Stream, typename T>
  Stream&
  operator<<(Stream& os, Type<T>)
  {
    static_assert(
      Config::RTTI_used,
      "This operator cannot be used without RTTI.  "
      "Please, provide your own definition if you do not want "
      "to use RTTI.");
    os << typeid(T).name();
    return os;
  }

  /**
   * @brief Given function on plane values and a type proxy, return a type proxy
   */
  template<typename F, typename T>
  constexpr auto type_transform(F, Type<T>)
  {
    return type<decay_t<result_of_t<F(T)>>>;
  }

  /**
   * @brief Given function on plane values and a type proxy, return a type proxy
   */
  template<typename F, typename T>
  constexpr auto type_transform(Type<T>)
  {
    return type<decay_t<result_of_t<F(T)>>>;
  }

  /**
   * @brief  Given a plane value, return a type proxy
   */
  template<typename T>
  constexpr auto
  type_pure(T&&)
  {
    return type<decay_t<T>>;
  }

  /**
   * @brief Given a type proxy to a function over plane types and a type proxy
   *  return a type proxy
   */
  template<typename F, typename T>
  constexpr auto type_apply(Type<F>, Type<T>)
  {
    return type<decay_t<result_of_t<F(T)>>>;
  }

  /**
   * @brief Bind a function taking a value and returning a type proxy with
   *  a type proxy
   */
  template<typename T, typename F>
  constexpr auto type_bind(Type<T>, F)
  {
    return result_of_t<F(T)>{};
  }

  /**
   * @brief Strip a layer off a type proxy
   */
  template<typename T>
  constexpr auto type_join(Type<Type<T>>)
  {
    return type<T>;
  }

  /**
   * @brief Inject a printed representation of a type proxy for char
   * to an output stream
   */
  template<typename Stream>
  Stream&
  operator<<(Stream& os, Type<char>)
  {
    os << "char";
    return os;
  }

  /**
   * @brief Inject a printed representation of a type proxy for unsigned char
   * to an output stream
   */
  template<typename Stream>
  Stream&
  operator<<(Stream& os, Type<unsigned char>)
  {
    os << "unsigned char";
    return os;
  }

  /**
   * @brief Inject a printed representation of a type proxy for singed char
   * to an output Stream
   */
  template<typename Stream>
  Stream&
  operator<<(Stream& os, Type<signed char>)
  {
    os << "signed char";
    return os;
  }

  /**
   * @brief Inject a printed representation of a type proxy for a wide char
   * (wchar_t) to an output Stream
   */
  template<typename Stream>
  Stream&
  operator<<(Stream& os, Type<wchar_t>)
  {
    os << "wchar_t";
    return os;
  }

  /**
   * @brief Inject a printed representation of a type proxy for a unicode
   * character (char16_t) to an output Stream
   */
  template<typename Stream>
  Stream&
  operator<<(Stream& os, Type<char16_t>)
  {
    os << "char16_t";
    return os;
  }

  /**
   * @brief Inject a printed representation of a type proxy for a unicode
   * character type (char32_t) to an output Stream
   */
  template<typename Stream>
  Stream&
  operator<<(Stream& os, Type<char32_t>)
  {
    os << "char32_t";
    return os;
  }

  /**
   * @brief Inject a prshorted representation of a type proxy for short
   * to an output Stream
   */
  template<typename Stream>
  Stream&
  operator<<(Stream& os, Type<short>)
  {
    os << "short";
    return os;
  }

  /**
   * @brief Inject a printed representation of a type proxy for int
   * to an output Stream
   */
  template<typename Stream>
  Stream&
  operator<<(Stream& os, Type<int>)
  {
    os << "int";
    return os;
  }

  /**
   * @brief Inject a prlonged representation of a type proxy for long
   * to an output Stream
   */
  template<typename Stream>
  Stream&
  operator<<(Stream& os, Type<long>)
  {
    os << "long";
    return os;
  }

  /**
   * @brief Inject a prlong longed representation of a type proxy for long long
   * to an output Stream
   */
  template<typename Stream>
  Stream&
  operator<<(Stream& os, Type<long long>)
  {
    os << "long long";
    return os;
  }

  /**
   * @brief Inject a prunsigned shorted representation of a type proxy for
   * unsigned short to an output Stream
   */
  template<typename Stream>
  Stream&
  operator<<(Stream& os, Type<unsigned short>)
  {
    os << "unsigned short";
    return os;
  }

  /**
   * @brief Inject a prunsigneded representation of a type proxy for unsigned
   * to an output Stream
   */
  template<typename Stream>
  Stream&
  operator<<(Stream& os, Type<unsigned>)
  {
    os << "unsigned";
    return os;
  }

  /**
   * @brief Inject a prunsigned longed representation of a type proxy for
   * unsigned long to an output Stream
   */
  template<typename Stream>
  Stream&
  operator<<(Stream& os, Type<unsigned long>)
  {
    os << "unsigned long";
    return os;
  }

  /**
   * @brief Inject a prunsigned long longed representation of a type proxy for
   * unsigned long long to an output Stream
   */
  template<typename Stream>
  Stream&
  operator<<(Stream& os, Type<unsigned long long>)
  {
    os << "unsigned long long";
    return os;
  }

  /**
   * @brief Inject a prfloated representation of a type proxy for float
   * to an output Stream
   */
  template<typename Stream>
  Stream&
  operator<<(Stream& os, Type<float>)
  {
    os << "float";
    return os;
  }

  /**
   * @brief Inject a prdoubleed representation of a type proxy for double
   * to an output Stream
   */
  template<typename Stream>
  Stream&
  operator<<(Stream& os, Type<double>)
  {
    os << "double";
    return os;
  }

  /**
   * @brief Inject a prlong doubleed representation of a type proxy for long
   * double to an output Stream
   */
  template<typename Stream>
  Stream&
  operator<<(Stream& os, Type<long double>)
  {
    os << "long double";
    return os;
  }

} // end of namespace TypeUtility::Core
