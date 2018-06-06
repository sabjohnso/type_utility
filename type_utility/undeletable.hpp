#ifndef UNDELETABLE_HPP_INCLUDED_1440085521649527419
#define UNDELETABLE_HPP_INCLUDED_1440085521649527419 1

//
// ... Type Utility header files
//
#include <type_utility/import.hpp>


namespace TypeUtility
{
  namespace Core
  {

    /** 
     * @brief A base class that cannot be deleted.
     *
     * @details This class is intended as a base class for 
     * base classes where the use of a virtual destructor is 
     * undesirable: where compile-time evaluation is desired 
     * and but would be prevented by the inclusion of a non-trivial
     * destructor.  Here, the delete operator is deleted, to prevent
     * unintended use.
     */
    class Undeletable
    {
    private:
      
      void operator delete ( void* ) = delete;
      void operator delete ( void*, align_val_t ) = delete;
      void operator delete ( void*, size_t ) = delete;
      void operator delete ( void*, size_t, align_val_t ) = delete;

      void operator delete []( void* ) = delete;
      void operator delete []( void*, align_val_t ) = delete;
      void operator delete []( void*, size_t ) = delete;
      void operator delete []( void*, size_t, align_val_t ) = delete;
      

    }; // end of class Undeletable
    
  } // end of namespace Core
} // end of namespace TypeUtility

#endif // !defined UNDELETABLE_HPP_INCLUDED_1440085521649527419
