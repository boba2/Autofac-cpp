#pragma once

#include "ServiceRegisterer.h"
#include "ServiceFactoryResolver.h"
#include "AutoManagedServiceResolver.h"
#include "SingletonServiceResolver.h"
#include "FunctionTraits.h"
#include "../ServiceFactoryRegisterer.h"

namespace DI
{
	namespace Details
	{

		template <class T, class FactoryType = T, class FactoryResultType = typename FunctionResultType<FactoryType>::Type, class ServiceType = typename UnderlyingType<FactoryResultType>::Type>
		class ServiceFactoryRegisterer : public ServiceRegisterer<ServiceType, DI::ServiceFactoryRegistererImpl>
		{
		public:
			using PublicType = DI::ServiceFactoryRegisterer<ServiceType, std::conditional_t<std::is_same<ServiceType*, FactoryResultType>::value, DI::NoAutoManage, void>>;

			explicit ServiceFactoryRegisterer(FactoryType factory)
				: _factory(factory)
			{}

			virtual void setSingleInstance() override
			{
				_single_instance = true;
			}

			virtual void setAutoManaged() override
			{
				_auto_managed = true;
			}

		private:
			virtual std::shared_ptr<ServiceResolver<>> getServiceResolver() const override
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