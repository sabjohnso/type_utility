//
// ... Type Utility header files
//
#include <type_utility/base_types.hpp>

//
// ... Testing header files
//
#include <gtest/gtest.h>

namespace TypeUtility::Core::Testing {
  TEST(type_utility, base_types)
  {
    ASSERT_EQ(type<Int<16>>.size(), 2);
    ASSERT_EQ(type<Int<32>>.size(), 4);
    ASSERT_EQ(type<Int<64>>.size(), 8);
    ASSERT_TRUE(type<Int<16>>.issigned());
    ASSERT_TRUE(type<Int<32>>.issigned());
    ASSERT_TRUE(type<Int<64>>.issigned());
    ASSERT_TRUE(type<Int<16>>.isintegral());
    ASSERT_TRUE(type<Int<32>>.isintegral());
    ASSERT_TRUE(type<Int<64>>.isintegral());
    ASSERT_TRUE(type<Int<16>>.isarithmetic());
    ASSERT_TRUE(type<Int<32>>.isarithmetic());
    ASSERT_TRUE(type<Int<64>>.isarithmetic());
    ASSERT_EQ(type<UInt<16>>.size(), 2);
    ASSERT_EQ(type<UInt<32>>.size(), 4);
    ASSERT_EQ(type<UInt<64>>.size(), 8);
    ASSERT_TRUE(type<UInt<16>>.isunsigned());
    ASSERT_TRUE(type<UInt<32>>.isunsigned());
    ASSERT_TRUE(type<UInt<64>>.isunsigned());
    ASSERT_TRUE(type<UInt<16>>.isintegral());
    ASSERT_TRUE(type<UInt<32>>.isintegral());
    ASSERT_TRUE(type<UInt<64>>.isintegral());
    ASSERT_TRUE(type<UInt<16>>.isarithmetic());
    ASSERT_TRUE(type<UInt<32>>.isarithmetic());
    ASSERT_TRUE(type<UInt<64>>.isarithmetic());
    ASSERT_EQ(type<Float<32>>.size(), 4);
    ASSERT_EQ(type<Float<64>>.size(), 8);
    ASSERT_EQ(type<Float<128>>.size(), 16);
    ASSERT_TRUE(type<Float<32>>.isfloating_point());
    ASSERT_TRUE(type<Float<64>>.isfloating_point());
    ASSERT_TRUE(type<Float<128>>.isfloating_point());
    ASSERT_TRUE(type<Float<32>>.isarithmetic());
    ASSERT_TRUE(type<Float<64>>.isarithmetic());
    ASSERT_TRUE(type<Float<128>>.isarithmetic());
  }

} // end of namespace TypeUtility::Testing
