#pragma once

namespace TypeUtility::Core {

  /**
   * @brief A base class for CRTP base classes
   *
   * @details This class implements the casts to the base class that
   * are used with the Curiously Recurring Template Pattern (CRTP).  It
   * is intented as a base class for base classes using CRTP to eliminate
   * the repetative reproduction of these cast operators. It should be noted
   * that the casts are not to the direct subtype
   *
   * The destructor is protected and default to protect from deletion of
   * pointers to this class and to allow use in compile-time calculations.
   *
   * @tparam K - A template template parameter representing the CRTP base class
   * whose specialization over T is the direct subtype of this class. This
   * parameter is only used for disambiguation in cases where multiple CRTP base
   * classes are use for a single target subtype. Conceivably, other templates
   * could satisfy this requirement, but a better choice is not likely
   *
   * @tparam T - A type template parameter that is the target type of the
   * casting operators.
   *
   * @tparam Ts - A parameter pack of types that may be use for additional
   * disabiguation.
   */
  template<template<typename...> class K, typename T, typename ... Ts>
  class CRTP
  {
  public:
    /**
     * @brief Cast to a const reference of the subtype
     */
    constexpr operator const T &() const&
    {
      return static_cast<const T&>(*this);
    }

    /**
     * @brief Cast to an rvalue reference of the subtype
     */
    constexpr
    operator T&&() &&
    {
      return static_cast<T&&>(*this);
    }

    /**
     * @brief Cast to a writable reference of the subtype
     */
    operator T&() & { return static_cast<T&>(*this); }

  protected:
    // Destructor is protected to only allow deletion from subtypes.  This
    // destructor is intentionally NOT virtual to allow  use as a base class
    // for compile time functionality.  Furthurmore, this class is not intended
    // be held as a polymorphic pointer on which delete might be executed.
    // Attempts, to delete a pointer to this base class indicate flawed
    // understanding of this class and CRTP in general.
    //
    // For the C++17 standard this causes problems as temporaries constructed
    // during the construction of subtypes cannot be destroyed.
#if 0
      CRTP()  = default;
      ~CRTP() = default;
#endif

  }; // end of class CRTP

} // end of namespace TypeUtility::Core
