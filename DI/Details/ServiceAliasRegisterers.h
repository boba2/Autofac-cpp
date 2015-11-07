#pragma once

#include "../Support/DIdecl.h"
#include "ServiceAliasRegisterer.h"
#include "ServiceResolvers.h"

namespace DI
{
	namespace Details
	{
		
		class DI_API ServiceAliasRegisterers
		{
		public:
			ServiceAliasRegisterers();
			ServiceAliasRegisterers(ServiceAliasRegisterers&& other);
			~ServiceAliasRegisterers();

			void add(std::shared_ptr<ServiceAliasRegisterer<>> alias_registerer);

			auto getServiceResolvers(std::shared_ptr<ServiceResolver<>> main_resolver) const->ServiceResolvers;

		private:
			class Impl;

#pragma warning(disable:4251)
			std::unique_ptr<Impl> _impl;
#pragma warning(default:4251)
		};

	}
}
