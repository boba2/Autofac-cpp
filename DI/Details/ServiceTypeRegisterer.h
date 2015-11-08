#pragma once

#include "ManageableServiceRegisterer.h"
#include "ServiceTypeResolver.h"

namespace DI
{
	namespace Details
	{

		template<class T>
		class ServiceTypeRegisterer : public ManageableServiceRegisterer<T>
		{
		public:
			using ServiceType = typename ManageableServiceRegisterer<T>::ServiceType;

		protected:
			virtual auto getMainServiceResolver() const -> ServiceResolverPtr<ServiceType> override
			{
				return std::make_shared<ServiceTypeResolver<ServiceType>>();
			}
		};

	}
}