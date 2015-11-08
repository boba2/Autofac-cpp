#pragma once

#include "ServiceRegisterer.h"
#include "ServiceTypeResolver.h"
#include "SingletonServiceResolver.h"
#include "AutoManagedServiceResolver.h"

namespace DI
{
	namespace Details
	{

		template<class T>
		class ServiceTypeRegisterer : public ServiceRegisterer
		{
		public:
			using ServiceType = T;

			virtual void setSingleInstance()
			{
				_single_instance = true;
			}

			virtual void setAutoManaged()
			{
				_auto_managed = true;
			}

		protected:
			virtual auto getServiceResolver() const -> ServiceResolverPtr<> override
			{
				auto resolver = getMainServiceResolver();
				if (_single_instance)
					resolver = std::make_shared<SingletonServiceResolver<ServiceType>>(resolver);
				if (_auto_managed)
					resolver = std::make_shared<AutoManagedServiceResolver<ServiceType>>(resolver);

				return resolver;
			}

		private:
			auto getMainServiceResolver() const -> ServiceResolverPtr<ServiceType>
			{
				return std::make_shared<ServiceTypeResolver<ServiceType>>();
			}

		private:
			bool _single_instance = false;
			bool _auto_managed = false;
		};

	}
}