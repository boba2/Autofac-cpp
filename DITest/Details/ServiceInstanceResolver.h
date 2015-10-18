#pragma once

#include "ServiceResolver.h"

namespace DI
{
	namespace Details
	{

		template<class T>
		class ServiceInstanceResolver : public ServiceResolver<T>
		{
		public:
			explicit ServiceInstanceResolver(std::shared_ptr<T> instance)
				: _instance(instance)
			{}

			virtual std::shared_ptr<T> getService() const override
			{
				return _instance;
			}

			virtual TypeIndex<> getServiceType() const override
			{
				return TypeIndex<T>();
			}

		private:
			std::shared_ptr<T> const _instance;
		};

	}
}