#pragma once

#include "ServiceRegisterer.h"
#include "ServiceInstanceResolver.h"
#include "../ServiceInstanceRegisterer.h"

namespace DI
{
	namespace Details
	{

		template<class T>
		class ServiceInstanceRegisterer : public ServiceRegisterer<typename UnderlyingType<T>::Type, DI::ServiceInstanceRegistererImpl>
		{
		public:
			using ServiceType = typename UnderlyingType<T>::Type;
			using PublicType = DI::ServiceInstanceRegisterer<ServiceType>;

			template<class U>
			explicit ServiceInstanceRegisterer(U &&instance)
				: _instance(std::make_shared<std::remove_reference_t<U>>(std::forward<U>(instance)))
			{}
			explicit ServiceInstanceRegisterer(ServiceType *const instance)
				: _instance(std::shared_ptr<ServiceType>(instance, NullDeleter()))
			{}
			explicit ServiceInstanceRegisterer(std::shared_ptr<ServiceType> instance)
				: _instance(instance)
			{}
			explicit ServiceInstanceRegisterer(std::unique_ptr<ServiceType> instance)
				: _instance(std::move(instance))
			{}

			virtual std::shared_ptr<ServiceResolver<>> getServiceResolver() const override
			{
				return std::make_shared<ServiceInstanceResolver<ServiceType>>(_instance);
			}

		private:
			struct NullDeleter
			{
				void operator()(ServiceType *) const {}
			};

			std::shared_ptr<ServiceType> _instance;
		};

	}
}