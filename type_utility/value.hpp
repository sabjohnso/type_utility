#pragma once

//
// ... Type Utility header files
//
#include <type_utility/import.hpp>

namespace TypeUtility {
  namespace Core {

    /**
     * @brief A base class for types holding a single value
     */
    template<typename T>
    class Value {
    public:
      using value_type = T;
      using reference = value_type&;
      using const_reference = const value_type&;
      using rvalue_reference = value_type&&;

      template<typename U, typename... Us>
      constexpr Value(U&& input, Us&&... inputs)
        : value(forward<U>(input), forward<Us>(inputs)...)
      {}

    protected:
      constexpr const_reference
      get() const&
      {
        return value;
      }

      constexpr rvalue_reference
      get() &&
      {
        return move(value);
      }

      reference
      mutable_get()
      {
        return value;
      }

    private:
      constexpr operator const_reference() const& { return value; }

      constexpr operator rvalue_reference() && { return move(value); }

      operator reference() & { return value; }

      value_type value;

    }; //  end of class Value

  } // end of namespace Core
} // end of namespace TypeUtility
