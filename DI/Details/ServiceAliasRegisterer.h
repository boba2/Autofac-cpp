#pragma once

#include "ServiceAliasResolver.h"

namespace DI
{
	namespace Details
	{

		template<class T = void, class S = void>
		class ServiceAliasRegisterer;

		template<>
		class ServiceAliasRegisterer<void, void>
		{
		public:
			virtual ~ServiceAliasRegisterer() {}

			virtual std::shared_ptr<ServiceResolver<>> getServiceAliasResolver(std::shared_ptr<ServiceResolver<>> main_resolver) const = 0;
		};

		template<class T, class S>
		class ServiceAliasRegisterer : public ServiceAliasRegisterer<>
		{
		public:
			virtual std::shared_ptr<ServiceResolver<>> getServiceAliasResolver(std::shared_ptr<ServiceResolver<>> main_resolver) const override
			{
				return getServiceAliasResolver<T, S>(main_resolver);
			}

			template<class U, class V>
			std::shared_ptr<ServiceResolver<>> getServiceAliasResolver(std::shared_ptr<ServiceResolver<>> main_resolver, std::enable_if_t<std::is_base_of<U, V>::value>* = 0) const
			{
				return std::make_shared<ServiceAliasResolver<T, S>>(std::dynamic_pointer_cast<ServiceResolver<S>>(main_resolver));
			}

			template<class U, class V>
			std::shared_ptr<ServiceResolver<>> getServiceAliasResolver(std::shared_ptr<ServiceResolver<>> main_resolver, std::enable_if_t<!std::is_base_of<U, V>::value>* = 0) const
			{
			}
		};

		template<class T>
		class ServiceAliasRegisterer<T, T> : public ServiceAliasRegisterer<>
		{
		public:
			virtual std::shared_ptr<ServiceResolver<>> getServiceAliasResolver(std::shared_ptr<ServiceResolver<>> main_resolver) const override
			{
				return main_resolver;
			}
		};

	}
}