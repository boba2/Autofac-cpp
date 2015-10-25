#pragma once

#include <functional>
#include "IndexSequence.h"

namespace DI
{
	namespace Details
	{
		namespace FunctionTraits
		{
			
			struct AnyType
			{
				template<class U>
				operator U() {};
			};

			template<class T, int>
			using WrapType = T;

			template<class T, class... As>
			decltype(std::declval<T>()(std::declval<As>()...), std::true_type()) IsCallable(int) {};
			template<class T, class...>
			std::false_type IsCallable(...) {};
			template<class T, class... As>
			using IsCallableCheck = decltype(IsCallable<T, As...>(0));

			template<template<class...> class, class, class, class = void>
			struct FunctionArityImpl;

			template<template<class...> class C, class T, int... I>
			struct FunctionArityImpl<C, T, IndexSequence<I...>, std::enable_if_t<(sizeof...(I) > 0) && C<T, WrapType<AnyType, I>...>::value>>
			{
				static constexpr int value = sizeof...(I);
			};

			template<template<class...> class C, class T, int... I>
			struct FunctionArityImpl<C, T, IndexSequence<I...>, std::enable_if_t<(sizeof...(I) > 0) && !C<T, WrapType<AnyType, I>...>::value>>
				: FunctionArityImpl<C, T, MakeIndexSequence<sizeof...(I)-1>>
			{};

			template<template<class...> class C, class T>
			struct FunctionArityImpl<C, T, IndexSequence<>>
			{
				static constexpr int value = 0;
			};

			template<class, class>
			struct FunctionResultTypeImpl;

			template<class T, int... I>
			struct FunctionResultTypeImpl<T, IndexSequence<I...>>
			{
				using Type = std::result_of_t<T(WrapType<AnyType, I>...)>;
			};

		}

		template<class T, int Max = 10>
		struct FunctionArity
		{
			static constexpr int value = FunctionTraits::FunctionArityImpl<FunctionTraits::IsCallableCheck, T, MakeIndexSequence<Max>>::value;
		};

		template<class T>
		struct FunctionResultType
		{
			using Type = typename FunctionTraits::FunctionResultTypeImpl<T, MakeIndexSequence<FunctionArity<T>::value>>::Type;
		};

	}
}