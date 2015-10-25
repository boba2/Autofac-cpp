#pragma once

#include "ServiceResolver.h"

namespace DI
{
	namespace Details
	{

		template<class T>
		struct ServiceReferenceTypeConverter
		{
			using Result = std::conditional_t<std::is_abstract<T>::value, const T&, T>;

			static Result convertFrom(ServiceResolver<T>& resolver, Container* container)
			{	
				return resolver.getService(container);
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<const T>
		{
			using Result = std::conditional_t<std::is_abstract<T>::value, const T&, T>;

			static Result convertFrom(ServiceResolver<T>& resolver, Container* container)
			{
				return resolver.getService(container);
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<T&>
		{
			using Result = T&;

			static Result convertFrom(ServiceResolver<T>& resolver, Container* container)
			{
				return resolver.getServiceAsRef(container);
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<const T&>
		{
			using Result = const T&;

			static Result convertFrom(ServiceResolver<T>& resolver, Container* container)
			{
				return resolver.getServiceAsRef(container);
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<T*>
		{
			using Result = T*;

			static Result convertFrom(ServiceResolver<T>& resolver, Container* container)
			{
				return resolver.getServiceAsPtr(container);
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<const T*>
		{
			using Result = const T*;

			static Result convertFrom(ServiceResolver<T>& resolver, Container* container)
			{
				return resolver.getServiceAsPtr(container);
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<std::shared_ptr<T>>
		{
			using Result = std::shared_ptr<T>;

			static Result convertFrom(ServiceResolver<T>& resolver, Container* container)
			{
				return resolver.getServiceAsSharedPtr(container);
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<std::shared_ptr<const T>>
		{
			using Result = std::shared_ptr<const T>;

			static Result convertFrom(ServiceResolver<T>& resolver, Container* container)
			{
				return resolver.getServiceAsSharedPtr(container);
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<std::unique_ptr<T>>
		{
			using Result = std::unique_ptr<T>;

			static Result convertFrom(ServiceResolver<T>& resolver, Container* container)
			{
				return resolver.getServiceAsUniquePtr(container);
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<std::unique_ptr<const T>>
		{
			using Result = std::unique_ptr<const T>;

			static Result convertFrom(ServiceResolver<T>& resolver, Container* container)
			{
				return resolver.getServiceAsUniquePtr(container);
			}
		};

	}
}
