#pragma once

#include <type_traits>
#include "IndexSequence.h"

namespace DI
{
	namespace Details
	{

		template<class T>
		struct AnyType
		{
			template<class U, class = std::enable_if_t<!std::is_same<T, U>::value>>
			operator U() {};
		};

		template<class T, class... As>
		decltype(void(T(std::declval<As>()...)), std::true_type()) IsConstructible(int) {};
		template<class T, class...>
		std::false_type IsConstructible(...) {};
		template<class T, class... As>
		using IsConstructibleCheck = decltype(IsConstructible<T, As...>(0));

		template<class T, int>
		using WrapType = T;

		template<template<class...> class, class, class, class = void>
		struct ConstructorArityImpl;

		template<template<class...> class C, class T, int... I>
		struct ConstructorArityImpl<C, T, IndexSequence<I...>, std::enable_if_t<(sizeof...(I) > 0) && C<T, WrapType<AnyType<T>, I>...>::value>>
		{
			static constexpr int value = sizeof...(I);
		};

		template<template<class...> class C, class T, int... I>
		struct ConstructorArityImpl<C, T, IndexSequence<I...>, std::enable_if_t<(sizeof...(I) > 0) && !C<T, WrapType<AnyType<T>, I>...>::value>>
			: ConstructorArityImpl<C, T, MakeIndexSequence<sizeof...(I)-1>>
		{};

		template<template<class...> class C, class T>
		struct ConstructorArityImpl<C, T, IndexSequence<>>
		{
			static constexpr int value = 0;
		};

		template<class T, int Max = 10>
		struct ConstructorArity
		{
			static constexpr int value = ConstructorArityImpl<IsConstructibleCheck, T, MakeIndexSequence<Max>>::value;
		};

	}
}