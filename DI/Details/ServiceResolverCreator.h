#pragma once

#include "ServiceResolver.h"
#include "TypeIndex.h"
#include "CompositeServiceResolver.h"

namespace DI
{
	namespace Details
	{
		class ServiceResolverCreator
		{
		public:
			virtual ~ServiceResolverCreator() {}

			virtual TypeIndex getServiceType() const = 0;
			virtual ServiceResolverPtr<> getServiceResolver() const = 0;
			virtual CompositeServiceResolverPtr<> createCompositeServiceResolver() const = 0;
		};

		using ServiceResolverCreatorPtr = std::shared_ptr<ServiceResolverCreator>;

		template<class T>
		class ConcreteServiceResolverCreator : public ServiceResolverCreator
		{
		public:
			explicit ConcreteServiceResolverCreator(ServiceResolverPtr<> resolver)
				: _resolver(resolver)
			{}

			static ServiceResolverCreatorPtr from(ServiceResolverPtr<> resolver)
			{
				return std::make_shared<ConcreteServiceResolverCreator<T>>(resolver);
			}

		private:
			virtual TypeIndex getServiceType() const override
			{
				static auto type_index = TypeIndex::from<T>();

				return type_index;
			}

			virtual ServiceResolverPtr<> getServiceResolver() const override
			{
				return _resolver;
			}

			virtual CompositeServiceResolverPtr<> createCompositeServiceResolver() const override
			{
				return std::make_shared<CompositeServiceResolver<T>>();
			}

			ServiceResolverPtr<> _resolver;
		};
	}
}