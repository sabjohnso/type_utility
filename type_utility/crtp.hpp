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

    enum class Base_delete_protection { optimism, undeletable, virtual_destructor };

    
    /**
     * @brief A base class for CRTP base classes that just hopes for the best and
     * ignores the issue of deleting a base class pointer.
     *
     * @details This class provides type casts to subtypes as a base for CRTP bases.
     * The majority of CRTP use is inconsistent with use cases where execution of the
     * delete operator over a CRTP base pointer would be reasonable. As such, the default 
     * behavior here is to just ignore the issue and expect uses of this class to
     * be as intended.  This facilitates use of this class as a base for compile time 
     * calculations.
     * 
     * However, stupid is as stupid does, so to alternative specializations are also
     * provided.  The first includes an undeletable base, which prevents invokation of
     * unspecified behavior, but may also prevent lagitimate use.  The second uses
     * public virtual destructor, as is costomary, but it will prevent use as a
     * base for compile time computation.
     */
    template< typename T, Base_delete_protection protection = Base_delete_protection::optimism >
    class CRTP{
    public:
      constexpr operator const T& () const & { return static_cast<const T&>( *this ); }
      constexpr operator T&& () && { return static_cast<T&&>( *this ); }
      operator T& () & { return static_cast<T&>( *this ); }

      virtual ~CRTP(){}
    };
    


    /** 
     * @brief A base class for CRTP base classes, inheriting from Undeletable
     */
    template< typename T >
    class CRTP<T,Base_delete_protection::undeletable> : Undeletable {
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

    
    
  } // end of namespace Core
} // end of namespace TypeUtility

#endif // !defined CRTP_HPP_INCLUDED_282592837431372485
