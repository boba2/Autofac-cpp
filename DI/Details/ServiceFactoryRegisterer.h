#pragma once

#include <functional>
#include "ServiceRegisterer.h"
#include "ServiceFactoryResolver.h"
#include "AutoManagedServiceResolver.h"
#include "Error/BadServiceDefinition.h"
#include "../ServiceFactoryRegisterer.h"

namespace DI
{
	namespace Details
	{

		template<class T>
		class ServiceFactoryRegisterer : public ServiceRegisterer<T, DI::ServiceFactoryRegisterer<T>>
		{
		public:
			template<class U, class = std::enable_if_t<!std::is_abstract<U>::value>>
			explicit ServiceFactoryRegisterer(std::function<U()> factory)
				: _shared_service_factory([factory] { return std::make_shared<T>(factory()); }),
				_unique_service_factory([factory] { return std::make_unique<T>(factory()); })
			{}
			explicit ServiceFactoryRegisterer(std::function<T*()> factory)
				: _shared_service_factory([factory] { return std::shared_ptr<T>(factory(), NullDeleter()); }),
				_ptr_service_factory(factory)
			{}
			explicit ServiceFactoryRegisterer(std::function<std::shared_ptr<T>()> factory)
				: _shared_service_factory(factory)
			{}
			explicit ServiceFactoryRegisterer(std::function<std::unique_ptr<T>()> factory)
				: _shared_service_factory([factory] { return std::shared_ptr<T>(std::move(factory())); }),
				_unique_service_factory(factory)
			{}

			virtual std::shared_ptr<ServiceResolver<>> getServiceResolver() const override
			{
				auto resolver = std::static_pointer_cast<ServiceResolver<T>>(std::make_shared<ServiceFactoryResolver<T>>(_shared_service_factory, _unique_service_factory, _ptr_service_factory));

				if (_auto_managed)
					resolver = std::make_shared<AutoManagedServiceResolver<T>>(resolver);

				return resolver;
			}

		protected:
			virtual void setAutoManaged() override
			{
				if (_ptr_service_factory)
					throw Error::BadServiceDefinition();

				_auto_managed = true;
			}

		private:
			struct NullDeleter
			{
				void operator()(T *) const {}
			};

		private:
			bool _auto_managed = false;
			std::function<std::shared_ptr<T>()> _shared_service_factory;
			std::function<std::unique_ptr<T>()> _unique_service_factory;
			std::function<T*()> _ptr_service_factory;
		};

	}
}