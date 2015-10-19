#pragma once

#include "ServiceRegisterer.h"
#include "ServiceTypeResolver.h"

namespace DI
{
	namespace Details
	{
		
		template<class T>
		class ServiceTypeRegisterer : public ServiceRegisterer<T>
		{
		public:
			virtual std::shared_ptr<ServiceResolver<>> getServiceResolver() const override
			{
				static_assert(!std::is_abstract<T>::value, "Cannot register an abstract type");

				return std::make_shared<ServiceTypeResolver<T>>();
			}
		};

	}
}