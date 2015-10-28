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
			
			struct AnyTypeRef
			{
				template<class U>
				operator U&() const {};
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
			struct FunctionArityImpl<C, T, IndexSequence<I...>, 
				std::enable_if_t<
					(sizeof...(I) > 0) 
					&& C<T, WrapType<AnyType, I>...>::value
				>
			>
			{
				static constexpr int value = sizeof...(I);
			};

			template<template<class...> class C, class T, int... I>
			struct FunctionArityImpl<C, T, IndexSequence<I...>,
				std::enable_if_t<
					(sizeof...(I) > 0)
					&& !C<T, WrapType<AnyType, I>...>::value
					&& C<T, WrapType<AnyTypeRef, I>...>::value
				>
			>
			{
				static constexpr int value = sizeof...(I);
			};

			template<template<class...> class C, class T, int... I>
			struct FunctionArityImpl<C, T, IndexSequence<I...>, 
				std::enable_if_t<
					(sizeof...(I) > 0) 
					&& !C<T, WrapType<AnyType, I>...>::value
					&& !C<T, WrapType<AnyTypeRef, I>...>::value
				>
			>
				: FunctionArityImpl<C, T, MakeIndexSequence<sizeof...(I) - 1>>
			{};

			template<template<class...> class C, class T>
			struct FunctionArityImpl<C, T, IndexSequence<>>
			{
				static constexpr int value = 0;
			};

			template<template<class...> class, class, class, class = void>
			struct FunctionResultTypeImpl;

			template<template<class...> class C, class T, int... I>
			struct FunctionResultTypeImpl<C, T, IndexSequence<I...>, std::enable_if_t<C<T, WrapType<AnyType, I>...>::value>>
			{
				using Type = std::result_of_t<T(WrapType<AnyType, I>...)>;
			};

			template<template<class...> class C, class T, int... I>
			struct FunctionResultTypeImpl<C, T, IndexSequence<I...>, std::enable_if_t<!C<T, WrapType<AnyType, I>...>::value>>
			{
				using Type = std::result_of_t<T(WrapType<AnyTypeRef, I>...)>;
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
			using Type = typename FunctionTraits::FunctionResultTypeImpl<FunctionTraits::IsCallableCheck, T, MakeIndexSequence<FunctionArity<T>::value>>::Type;
		};

	}
}