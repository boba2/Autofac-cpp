#pragma once

#include "ServiceResolver.h"

namespace DI
{
	namespace Details
	{

		template<class T>
		struct ServiceReferenceTypeConverter
		{
			static const T& convertFrom(ServiceResolver<T>& resolver)
			{	
				return resolver.getServiceAsConstRef();
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<T&>
		{
			static T& convertFrom(ServiceResolver<T>& resolver)
			{
				return resolver.getServiceAsRef();
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<T*>
		{
			static T* convertFrom(ServiceResolver<T>& resolver)
			{
				return resolver.getServiceAsPtr();
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<std::shared_ptr<T>>
		{
			static std::shared_ptr<T> convertFrom(ServiceResolver<T>& resolver)
			{
				return resolver.getServiceAsSharedPtr();
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<std::shared_ptr<T> &>
		{
			static std::shared_ptr<T> convertFrom(ServiceResolver<T>& resolver)
			{
				return resolver.getServiceAsSharedPtr();
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<std::unique_ptr<T>>
		{
			static std::unique_ptr<T> convertFrom(ServiceResolver<T>& resolver)
			{
				return resolver.getServiceAsUniquePtr();
			}
		};

	}
}
