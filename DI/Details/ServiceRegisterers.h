#pragma once

#include "../Support/DIdecl.h"
#include "ServiceRegisterer.h"
#include <functional>

namespace DI
{
	namespace Details
	{

		class DI_API ServiceRegisterers
		{
		public:
			ServiceRegisterers();
			ServiceRegisterers(ServiceRegisterers&& other);
			~ServiceRegisterers();

			void add(std::shared_ptr<ServiceRegisterer<>> registerer);
			void forEach(std::function<void(const ServiceRegisterer<>&)> action) const;

		private:
			class Impl;

#pragma warning(disable:4251)
			std::unique_ptr<Impl> _impl;
#pragma warning(default:4251)
		};

	}
}
