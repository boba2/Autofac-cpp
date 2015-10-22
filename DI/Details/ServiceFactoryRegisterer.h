#pragma once

#include <functional>
#include "ServiceRegisterer.h"
#include "ServiceFactoryResolver.h"

namespace DI
{
	namespace Details
	{

		template<class T>
		class ServiceFactoryRegisterer : public ServiceRegisterer<T>
		{
		public:
			template<class U, class = std::enable_if_t<std::is_same<T, U>::value && !std::is_abstract<U>::value && !std::is_pointer<U>::value>>
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
				return std::make_shared<ServiceFactoryResolver<T>>(_shared_service_factory, _unique_service_factory, _ptr_service_factory);
			}

		protected:
			virtual void registerAlias(std::shared_ptr<ServiceAliasRegisterer<>> alias_registerer) override
			{
				ServiceRegisterer<T>::registerAlias(alias_registerer);
			}

		private:
			struct NullDeleter
			{
				void operator()(T *) const {}
			};

			std::function<std::shared_ptr<T>()> _shared_service_factory;
			std::function<std::unique_ptr<T>()> _unique_service_factory;
			std::function<T*()> _ptr_service_factory;
		};

	}
}