#pragma once

#include "ServiceRegisterer.h"
#include "ServiceFactoryResolver.h"
#include "AutoManagedServiceResolver.h"
#include "SingletonServiceResolver.h"
#include "FunctionTraits.h"

namespace DI
{
	namespace Details
	{

		template <class T, class FactoryType = T, class FactoryResultType = typename FunctionResultType<FactoryType>::Type, class ServiceType = typename UnderlyingType<FactoryResultType>::Type>
		class ServiceFactoryRegisterer : public ServiceRegisterer<ServiceType>
		{
		public:
			explicit ServiceFactoryRegisterer(FactoryType factory)
				: _factory(factory)
			{}

			virtual void setSingleInstance()
			{
				_single_instance = true;
			}

			virtual void setAutoManaged()
			{
#pragma warning(disable:4127)
				if (std::is_pointer<FactoryResultType>::value)
					throw std::logic_error("Service created through a factory function returning a raw pointer cannot be auto-managed");
#pragma warning(default:4127)

				_auto_managed = true;
			}

		private:
			virtual ServiceResolverPtr<> getServiceResolver() const override
			{
				auto resolver = std::static_pointer_cast<ServiceResolver<ServiceType>>(std::make_shared<ServiceFactoryResolver<FactoryType>>(_factory));

				if (_single_instance)
					resolver = std::make_shared<SingletonServiceResolver<ServiceType>>(resolver);
				if (_auto_managed)
					resolver = std::make_shared<AutoManagedServiceResolver<ServiceType>>(resolver);

				return resolver;
			}

		private:
			bool _single_instance = false;
			bool _auto_managed = false;
			FactoryType _factory;
		};

	}
}