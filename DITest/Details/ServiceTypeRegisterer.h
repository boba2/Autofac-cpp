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
				return std::make_shared<ServiceTypeResolver<T>>();
			}
		};

	}
}