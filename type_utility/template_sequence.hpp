#pragma once

namespace TypeUtility::Core {

  template<template<typename...> typename... Ks>
  class Template_sequence {}; // end of class

  template<template<typename...> typename... Ks>
  constexpr Template_sequence<Ks...> templates{};

} // end of namespace TypeUtility::Core
