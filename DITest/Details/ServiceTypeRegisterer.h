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
			virtual std::set<std::shared_ptr<ServiceResolver<>>> getServiceResolvers() const override
			{
				std::set<std::shared_ptr<ServiceResolver<>>> result;

				auto resolver = std::make_shared<ServiceTypeResolver<T>>();
				result.insert(resolver);

				return result;
			}
		};

	}
}