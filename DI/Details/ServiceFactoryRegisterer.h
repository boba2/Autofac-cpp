#pragma once

#include "ManageableServiceRegisterer.h"
#include "ServiceFactoryResolver.h"
#include "FunctionTraits.h"

namespace DI
{
	namespace Details
	{

		template <class T>
		class ServiceFactoryRegisterer : public ManageableServiceRegisterer<typename UnderlyingType<typename FunctionResultType<T>::Type>::Type>
		{
		public:
			using FactoryType = T;
			using FactoryResultType = typename FunctionResultType<FactoryType>::Type;
			using ServiceType = typename UnderlyingType<FactoryResultType>::Type;

			explicit ServiceFactoryRegisterer(FactoryType factory)
				: _factory(factory)
			{}

			void setAutoManaged()
			{
#pragma warning(disable:4127)
				if (std::is_pointer<FactoryResultType>::value)
					throw std::logic_error("Service created through a factory function returning a raw pointer cannot be auto-managed");
#pragma warning(default:4127)

				ManageableServiceRegisterer<ServiceType>::setAutoManaged();
			}

		protected:
			virtual auto getMainServiceResolver() const -> ServiceResolverPtr<ServiceType> override
			{
				return std::make_shared<ServiceFactoryResolver<ServiceType, FactoryType>>(_factory);
			}

		private:
			FactoryType _factory;
		};

	}
}