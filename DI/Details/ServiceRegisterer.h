#pragma once

#include "../Support/DIdecl.h"
#include "ServiceResolver.h"
#include "ServiceAliasRegisterer.h"
#include "ServiceResolvers.h"

namespace DI
{
	namespace Details
	{

		class DI_API ServiceRegisterer
		{
		public:
			ServiceRegisterer();
			ServiceRegisterer(ServiceRegisterer&&);
			virtual ~ServiceRegisterer();
			
			void registerAlias(ServiceAliasRegistererPtr<> alias_registerer);
			auto getServiceResolvers() const -> ServiceResolvers;

		protected:
			virtual auto getServiceResolver() const -> ServiceResolverData = 0;

		private:
			class Impl;

#pragma warning(disable:4251)
			std::unique_ptr<Impl> _impl;
#pragma warning(default:4251)
		};

		typedef std::shared_ptr<ServiceRegisterer> ServiceRegistererPtr;

	}
}