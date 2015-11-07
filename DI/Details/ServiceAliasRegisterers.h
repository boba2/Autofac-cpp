#pragma once

#include "../Support/DIdecl.h"
#include "ServiceAliasRegisterer.h"
#include <functional>

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

			void forEach(std::function<void(const ServiceAliasRegisterer<>&)> action) const;

		private:
			class Impl;

#pragma warning(disable:4251)
			std::unique_ptr<Impl> _impl;
#pragma warning(default:4251)
		};

	}
}
