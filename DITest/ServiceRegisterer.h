#pragma once

#include <memory>
#include "ServiceResolver.h"

namespace DI
{
	namespace Details
	{

		template<class T = void>
		class ServiceRegisterer;

		template<>
		class ServiceRegisterer<void>
		{
		public:
			virtual ~ServiceRegisterer() {}

			virtual std::shared_ptr<ServiceResolver<>> getServiceResolver() const = 0;
		};

	}
}