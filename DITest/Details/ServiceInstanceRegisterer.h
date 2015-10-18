#pragma once

#include "ServiceRegisterer.h"
#include "ServiceInstanceResolver.h"

namespace DI
{
	namespace Details
	{

		template<class T>
		class ServiceInstanceRegisterer : public ServiceRegisterer<T>
		{
		public:
			template<class U>
			explicit ServiceInstanceRegisterer(U &&instance)
				: _instance(std::make_shared<std::remove_reference_t<U>>(std::forward<U>(instance)))
			{}
			explicit ServiceInstanceRegisterer(T *const instance)
				: _instance(std::shared_ptr<T>(instance, NullDeleter()))
			{}
			explicit ServiceInstanceRegisterer(std::shared_ptr<T> instance)
				: _instance(instance)
			{}
			explicit ServiceInstanceRegisterer(std::unique_ptr<T> instance)
				: _instance(std::move(instance))
			{}

			std::set<std::shared_ptr<ServiceResolver<>>> getServiceResolvers() const override
			{
				auto main_resolver = std::make_shared<ServiceInstanceResolver<T>>(_instance);

				std::set<std::shared_ptr<ServiceResolver<>>> result;

				auto alias_resolvers = getServiceAliasResolvers(main_resolver);
				if (alias_resolvers.empty())
					result.insert(main_resolver);
				else
					result.insert(begin(alias_resolvers), end(alias_resolvers));

				return result;
			}

		private:
			struct NullDeleter
			{
				void operator()(T *) const {}
			};

			std::shared_ptr<T> _instance;
		};

	}
}