#pragma once

#include <memory>
#include "TypeIndex.h"

namespace DI
{
	namespace Details
	{

		template<class T = void>
		class ServiceResolver;

		template<>
		class ServiceResolver<void>
		{
		public:
			virtual ~ServiceResolver() {}

			virtual TypeIndex<> getServiceType() const = 0;
		};

		template<class T>
		class ServiceResolver : public ServiceResolver<>
		{
		public:
			virtual std::shared_ptr<T> getService() const = 0;
		};

	}
}