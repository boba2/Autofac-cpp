#pragma once

#include <functional>
#include "ServiceRegisterer.h"
#include "ServiceFactoryResolver.h"
#include "AutoManagedServiceResolver.h"
#include "../ServiceFactoryRegisterer.h"

namespace DI
{
	namespace Details
	{

		template<class T>
		class ServiceFactoryRegisterer : public ServiceRegisterer<typename UnderlyingType<decltype(std::declval<T>()())>::Type, DI::ServiceFactoryRegistererImpl>
		{
		public:
			using FactoryResultType = decltype(std::declval<T>()());
			using ServiceType = typename UnderlyingType<FactoryResultType>::Type;
			using PublicType = DI::ServiceFactoryRegisterer<ServiceType, std::conditional_t<std::is_same<ServiceType*, FactoryResultType>::value, DI::NoAutoManage, void>>;

			template<class S>
			explicit ServiceFactoryRegisterer(S factory)
			{
				setFactories(static_cast<std::function<FactoryResultType()>>(factory));
			}

		private:
			template<class V, class = std::enable_if_t<!std::is_abstract<V>::value>>
			void setFactories(std::function<V()> factory)
			{
				_shared_service_factory = [factory] { return std::make_shared<ServiceType>(factory()); };
				_unique_service_factory = [factory] { return std::make_unique<ServiceType>(factory()); };
			}
			void setFactories(std::function<ServiceType*()> factory)
			{
				_shared_service_factory = [factory] { return std::shared_ptr<ServiceType>(factory(), NullDeleter()); };
				_ptr_service_factory = factory;
			}
			void setFactories(std::function<std::shared_ptr<ServiceType>()> factory)
			{
				_shared_service_factory = factory;
			}
			void setFactories(std::function<std::unique_ptr<ServiceType>()> factory)
			{
				_shared_service_factory = [factory] { return std::shared_ptr<ServiceType>(std::move(factory())); };
				_unique_service_factory = factory;
			}

			virtual std::shared_ptr<ServiceResolver<>> getServiceResolver() const override
			{
				auto resolver = std::static_pointer_cast<ServiceResolver<ServiceType>>(std::make_shared<ServiceFactoryResolver<ServiceType>>(_shared_service_factory, _unique_service_factory, _ptr_service_factory));

				if (_auto_managed)
					resolver = std::make_shared<AutoManagedServiceResolver<ServiceType>>(resolver);

				return resolver;
			}

		protected:
			virtual void setAutoManaged() override
			{
				_auto_managed = true;
			}

		private:
			struct NullDeleter
			{
				void operator()(ServiceType *) const {}
			};

		private:
			bool _auto_managed = false;
			std::function<std::shared_ptr<ServiceType>()> _shared_service_factory;
			std::function<std::unique_ptr<ServiceType>()> _unique_service_factory;
			std::function<ServiceType*()> _ptr_service_factory;
		};

	}
}