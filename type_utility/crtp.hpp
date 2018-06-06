#ifndef CRTP_HPP_INCLUDED_282592837431372485
#define CRTP_HPP_INCLUDED_282592837431372485 1

//
// ... Type Utility header files
//
#include <type_utility/undeletable.hpp>


namespace TypeUtility
{
  namespace Core
  {

    enum class Base_delete_protection { undeletable, virtual_destructor, optimism };

    /** 
     * @brief A base class for CRTP base classes, inheriting from Undeletable
     */
    template< typename T, Base_delete_protection mode = Base_delete_protection::undeletable >
    class CRTP : Undeletable {
    public:
      constexpr operator const T& () const & { return static_cast<const T&>( *this ); }
      constexpr operator T&& () && { return static_cast<T&&>( *this ); }
      operator T& () & { return static_cast<T&>( *this ); }
    };

    /**
     * @brief A base class for CRTP base classes with a virtual destructor
     */
    template< typename T >
    class CRTP<T,Base_delete_protection::virtual_destructor>{
    public:
      constexpr operator const T& () const & { return static_cast<const T&>( *this ); }
      constexpr operator T&& () && { return static_cast<T&&>( *this ); }
      operator T& () & { return static_cast<T&>( *this ); }

      virtual ~CRTP(){}
    };


    /**
     * @brief A base class for CRTP base classes that just hopes for the best and
     * ignores the issue of deleting a base class pointer.
     */
    template< typename T >
    class CRTP<T,Base_delete_protection::optimism>{
    public:
      constexpr operator const T& () const & { return static_cast<const T&>( *this ); }
      constexpr operator T&& () && { return static_cast<T&&>( *this ); }
      operator T& () & { return static_cast<T&>( *this ); }

      virtual ~CRTP(){}
    };
    
    
    
  } // end of namespace Core
} // end of namespace TypeUtility

#endif // !defined CRTP_HPP_INCLUDED_282592837431372485
