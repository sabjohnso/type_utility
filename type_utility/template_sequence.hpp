#pragma once

namespace TypeUtility::Core {

  template<template<typename ...> typename ... Ks>
  class Templates{};

  template<template<typename...> typename... Ks>
  using Template_sequence = Templates<Ks...>;

  template<template<typename...> typename... Ks>
  constexpr Template_sequence<Ks...> templates{};

} // end of namespace TypeUtility::Core
