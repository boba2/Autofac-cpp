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
			explicit ServiceFactoryRegisterer(T(factory)())
				: _factory([factory] { return std::make_shared<T>(factory()); })
			{}
			explicit ServiceFactoryRegisterer(T*(factory)())
				: _factory([factory] { return std::shared_ptr<T>(factory(), NullDeleter()); })
			{}
			explicit ServiceFactoryRegisterer(std::shared_ptr<T>(factory)())
				: _factory(factory)
			{}
			explicit ServiceFactoryRegisterer(std::unique_ptr<T>(factory)())
				: _factory([factory] { return std::move(factory());  })
			{}

			virtual std::shared_ptr<ServiceResolver<>> getServiceResolver() const override
			{
				static_assert(!std::is_abstract<T>::value, "Cannot register an abstract type");

				return std::make_shared<ServiceFactoryResolver<T>>(_factory);
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

			std::function<std::shared_ptr<T>()> _factory;
		};

	}
}