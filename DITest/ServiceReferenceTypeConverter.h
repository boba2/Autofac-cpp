#pragma once

#include <memory>
#include "Error.h"

namespace DI
{
	namespace Details
	{

		template<class T>
		struct ServiceReferenceTypeConverter
		{
			static const T &convert(std::shared_ptr<T> instance)
			{
				return *instance.get();
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<T &>
		{
			static T &convert(std::shared_ptr<T> instance)
			{
				return *instance.get();
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<T *>
		{
			static T *convert(std::shared_ptr<T> instance)
			{
				return instance.get();
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<std::shared_ptr<T>>
		{
			static std::shared_ptr<T> convert(std::shared_ptr<T> instance)
			{
				return instance;
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<std::shared_ptr<T> &>
		{
			static std::shared_ptr<T> convert(std::shared_ptr<T> instance)
			{
				return instance;
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<std::unique_ptr<T>>
		{
			static std::unique_ptr<T> convert(std::shared_ptr<T>)
			{
				throw Error::ServiceInstanceNotResolvableAsUniquePtr();
			}
		};

	}
}
