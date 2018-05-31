#ifndef BASE_TYPES_HPP_INCLUDED_2173693085049882071
#define BASE_TYPES_HPP_INCLUDED_2173693085049882071 1

namespace TypeUtility
{
  namespace Core
  {

    constexpr signed_integer_types =
      types<short,int,long,long long>;
    
    constexpr unsigned_integer_types =
      types<unsigned short,unsigned, unsigned long, unsigned long long>;

    constexpr floating_point_types =
      types<float, double, long double>;

    
    
  } // end of namespace Core
} // end of namespace TYPE_UTILITY_NAMESPACE


#endif // !defined BASE_TYPES_HPP_INCLUDED_2173693085049882071
