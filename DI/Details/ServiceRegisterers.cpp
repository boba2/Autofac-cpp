#include "ServiceRegisterers.h"

#include "ServiceRegisterer.h"
#include <algorithm>
#include <vector>

namespace DI
{
	namespace Details
	{
		
		class ServiceRegisterers::Impl
		{
		public:
			void add(std::shared_ptr<ServiceRegisterer<>> registerer)
			{
				_service_registerers.push_back(registerer);
			}

			void forEach(std::function<void(const ServiceRegisterer<>&)> action) const
			{
				std::for_each(
					begin(_service_registerers), end(_service_registerers),
					[&action](auto registerer) { action(*registerer); }
				);
			}

		private:
			std::vector<std::shared_ptr<ServiceRegisterer<>>> _service_registerers;
		};

		ServiceRegisterers::ServiceRegisterers()
			: _impl(std::make_unique<Impl>())
		{}

		ServiceRegisterers::ServiceRegisterers(ServiceRegisterers&& other)
			: _impl(std::move(other._impl))
		{}

		ServiceRegisterers::~ServiceRegisterers()
		{}

		void ServiceRegisterers::add(std::shared_ptr<ServiceRegisterer<>> registerer)
		{
			_impl->add(registerer);
		}

		void ServiceRegisterers::forEach(std::function<void(const ServiceRegisterer<>&)> action) const
		{
			_impl->forEach(action);
		}

	}
}