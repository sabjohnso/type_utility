//
// ... Type Utility header files
//
#include <type_utility/type_sequence.hpp>

//
// ... Testing header files
//
#include <gtest/gtest.h>
namespace TypeUtility::Core::Testing {

  TEST(type_utility, sequence_count_test)
  {
    ASSERT_EQ(count_types<>(), 0);
    ASSERT_EQ(count_types<int>(), 1);
    ASSERT_EQ((count_types<int, double>()), 2);
    ASSERT_EQ(count_types<>(), 0);
    ASSERT_EQ(count_types<int>(), 1);
    ASSERT_EQ((count_types<int, double>()), 2);
  }

  TEST(type_utility, sequence_has_type_test)
  {
    ASSERT_TRUE(!Has_type<int>::value);
    ASSERT_TRUE((Has_type<int, int>::value));
    ASSERT_TRUE((!Has_type<int, double>::value));
    ASSERT_TRUE((Has_type<int, char, int>::value));
    ASSERT_TRUE((!Has_type<int>::value));
    ASSERT_TRUE((Has_type<int, int>::value));
    ASSERT_TRUE((!Has_type<int, double>::value));
    ASSERT_TRUE((Has_type<int, char, int>::value));
  }

  TEST(type_utility, find_type_test)
  {
    ASSERT_EQ((Find_type<int, int>::value), 0);
    ASSERT_EQ((Find_type<int, char, int>::value), 1);
    ASSERT_EQ((Find_type<int, char, int, double>::value), 1);
    ASSERT_EQ((Find_type<char, char, short, int, long>::value), 0);
    ASSERT_EQ((Find_type<short, char, short, int, long>::value), 1);
    ASSERT_EQ((Find_type<int, char, short, int, long>::value), 2);
    ASSERT_EQ((Find_type<long, char, short, int, long>::value), 3);
    ASSERT_EQ((Find_type<int, int>::value), 0);
    ASSERT_EQ((Find_type<int, char, int>::value), 1);
    ASSERT_EQ((Find_type<int, char, int, double>::value), 1);
  }

  TEST(type_utility, sequence_test)
  {
    ASSERT_EQ((types<char, short, int, long>.size()), 4);
    ASSERT_TRUE((types<char, short, int, long>.ismember<char>()));
    ASSERT_TRUE((types<char, short, int, long>.ismember<short>()));
    ASSERT_TRUE((types<char, short, int, long>.ismember<int>()));
    ASSERT_TRUE((types<char, short, int, long>.ismember<long>()));
    ASSERT_TRUE((!types<char, short, int, long>.ismember<double>()));
    ASSERT_EQ((types<char, short, int, long>.find<char>()), 0);
    ASSERT_EQ((types<char, short, int, long>.find<short>()), 1);
    ASSERT_EQ((types<char, short, int, long>.find<int>()), 2);
    ASSERT_EQ((types<char, short, int, long>.find<long>()), 3);
    ASSERT_EQ((types<char, short, int, long>.at<0>()), type<char>);
    ASSERT_EQ((types<char, short, int, long>.at<1>()), type<short>);
    ASSERT_EQ((types<char, short, int, long>.at<2>()), type<int>);
    ASSERT_EQ((types<char, short, int, long>.at<3>()), type<long>);
    ASSERT_EQ((types<char, short, int, long>.size()), 4);
    ASSERT_TRUE((types<char, short, int, long>.ismember<char>()));
    ASSERT_TRUE((types<char, short, int, long>.ismember<short>()));
    ASSERT_TRUE((types<char, short, int, long>.ismember<int>()));
    ASSERT_TRUE((types<char, short, int, long>.ismember<long>()));
    ASSERT_TRUE((!types<char, short, int, long>.ismember<double>()));
    ASSERT_EQ((types<char, short, int, long>.find<char>()), 0);
    ASSERT_EQ((types<char, short, int, long>.find<short>()), 1);
    ASSERT_EQ((types<char, short, int, long>.find<int>()), 2);
    ASSERT_EQ((types<char, short, int, long>.find<long>()), 3);
    ASSERT_EQ((types<char, short, int, long>.at<0>()), type<char>);
    ASSERT_EQ((types<char, short, int, long>.at<1>()), type<short>);
    ASSERT_EQ((types<char, short, int, long>.at<2>()), type<int>);
    ASSERT_EQ((types<char, short, int, long>.at<3>()), type<long>);
  }

  TEST(type_utility, list_test)
  {
    constexpr auto char_types =
      type_list(type<char>, type<char16_t>, type<char32_t>);
    ASSERT_EQ(char_types, (types<char, char16_t, char32_t>));
    ASSERT_EQ(length(char_types), 3);
    ASSERT_EQ(head(char_types), type<char>);
    ASSERT_EQ(tail(char_types), (types<char16_t, char32_t>));
    ASSERT_EQ(reverse(char_types), (types<char32_t, char16_t, char>));
    ASSERT_EQ(
      append(char_types, char_types),
      (types<char, char16_t, char32_t, char, char16_t, char32_t>));

    constexpr auto to_int = [](auto x) { return int(x); };

    ASSERT_EQ(type_sequence_transform<decltype(to_int)>(types<>), types<>);
    ASSERT_EQ(type_sequence_transform(to_int, types<>), types<>);
    ASSERT_EQ(
      type_sequence_transform(to_int, char_types), (types<int, int, int>));

    if constexpr (Config::RTTI_used) {
      ASSERT_EQ(type_sequence_pure(to_int), types<decay_t<decltype(to_int)>>);
    }

    ASSERT_EQ(
      type_sequence_apply(type_sequence_pure(to_int), char_types),
      (types<int, int, int>));
    ASSERT_EQ(
      type_sequence_bind(
        char_types, [](auto x) { return type_sequence_pure(x); }),
      char_types);
  }

  TEST(type_utility, select_test)
  {
    ASSERT_EQ(
      select(types<short, int, long, long long>, index_sequence<0, 2>()),
      (types<short, long>));
    ASSERT_EQ(
      select(types<short, int, long, long long>, index_sequence<0, 2>()),
      (types<short, long>));
  }

} // end of namespace TypeUtility::Core::Testing
