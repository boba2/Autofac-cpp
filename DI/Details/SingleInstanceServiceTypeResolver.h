#pragma once
#include "ServiceResolver.h"
#include "Error/ServiceInstanceNotResolvableAs.h"

namespace DI
{
	namespace Details
	{

		template<class T>
		class SingleInstanceServiceTypeResolver : public ServiceResolver<T>
		{
			using ServiceType = typename ServiceResolver<T>::ServiceType;
			using ServiceRefType = typename ServiceResolver<T>::ServiceRefType;
			using ServicePtrType = typename ServiceResolver<T>::ServicePtrType;
			using ServiceSharedPtrType = typename ServiceResolver<T>::ServiceSharedPtrType;
			using ServiceUniquePtrType = typename ServiceResolver<T>::ServiceUniquePtrType;

			virtual ServiceType getService() const override
			{
				throw std::logic_error("Not implemented");
			}

			virtual ServiceRefType getServiceAsRef() const override
			{
				throw std::logic_error("Not implemented");
			}

			virtual ServicePtrType getServiceAsPtr() const override
			{
				throw std::logic_error("Not implemented");
			}

			virtual ServiceSharedPtrType getServiceAsSharedPtr() const override
			{
				if (!_instance)
					_instance = std::make_shared<T>();

				return _instance;
			}

			virtual ServiceUniquePtrType getServiceAsUniquePtr() const override
			{
				throw std::logic_error("Not implemented");
			}

		private:
			mutable ServiceSharedPtrType _instance; // @todo: remove 'mutable'
		};

	}
}