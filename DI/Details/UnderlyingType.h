#pragma once

#include <memory>
#include <vector>

namespace DI
{
	namespace Details
	{

		template<class T>
		struct UnderlyingType
		{
			using Type = T;
		};

		template<class T>
		struct UnderlyingType<const T>
		{
			using Type = T;
		};

		template<class T>
		struct UnderlyingType<T *>
		{
			using Type = typename UnderlyingType<T>::Type;
		};

		template<class T>
		struct UnderlyingType<T &>
		{
			using Type = typename UnderlyingType<T>::Type;
		};

		template<class T>
		struct UnderlyingType<T &&>
		{
			using Type = typename UnderlyingType<T>::Type;
		};

		template<class T>
		struct UnderlyingType<std::shared_ptr<T>>
		{
			using Type = typename UnderlyingType<T>::Type;
		};

		template<class T>
		struct UnderlyingType<std::unique_ptr<T>>
		{
			using Type = typename UnderlyingType<T>::Type;
		};

		template<class T>
		struct UnderlyingType<std::vector<T>>
		{
			using Type = typename UnderlyingType<T>::Type;
		};
	}
}