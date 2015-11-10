#pragma once

#include "ServiceRegisterer.h"
#include "SingletonServiceResolver.h"
#include "AutoManagedServiceResolver.h"

namespace DI
{
	namespace Details
	{
		
		template<class T>
		class ManageableServiceRegisterer : public ServiceRegisterer
		{
		public:
			using ServiceType = T;

			void setSingleInstance()
			{
				_single_instance = true;
			}

			void setAutoManaged()
			{
				_auto_managed = true;
			}

		protected:
			virtual auto getServiceResolver() const -> ServiceResolverData override
			{
				auto resolver = getMainServiceResolver();

				if (_single_instance)
					resolver = std::make_shared<SingletonServiceResolver<ServiceType>>(resolver);
				if (_auto_managed)
					resolver = std::make_shared<AutoManagedServiceResolver<ServiceType>>(resolver);

				return ServiceResolverData{TypeIndex::from<ServiceType>(), resolver};
			}

			virtual auto getMainServiceResolver() const -> ServiceResolverPtr<ServiceType> = 0;

		private:
			bool _single_instance = false;
			bool _auto_managed = false;
		};

	}
}