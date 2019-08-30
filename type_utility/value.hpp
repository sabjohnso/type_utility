#pragma once

//
// ... Type Utility header files
//
#include <type_utility/import.hpp>

namespace TypeUtility
{
  namespace Core
  {


    /** 
     * @brief A base class for types holding a single value
     */
    template< typename T >
    class Value
    {
    public:
      using value_type = T;
      using reference = value_type&;
      using const_reference = const value_type&;
      using rvalue_reference = value_type&&;
      
      template< typename ... Ts >
      constexpr
      Value( Ts&& ... inputs ) : value( forward<Ts>( inputs ) ... ){}

    protected:

      constexpr
      const_reference
      get() const & { return value; }

      constexpr
      rvalue_reference
      get() && { return move(value); }

      reference
      mutable_get(){ return value; }
	

    private:
      
      constexpr      
      operator const value_type& () const & { return value; }

      constexpr
      operator value_type&& () && { return value; }
      
      value_type value;
    }; //  end of class Value
    
    
  } // end of namespace Core
} // end of namespace TypeUtility

