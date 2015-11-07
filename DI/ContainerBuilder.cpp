#include "ContainerBuilder.h"

#include <algorithm>

namespace DI
{
	
	class ContainerBuilder::Impl
	{
	public:
		void addRegisterer(std::shared_ptr<Details::ServiceRegisterer<>> registerer)
		{
			_service_registerers.push_back(registerer);
		}

		Container buildContainer() const
		{
			auto service_resolvers = Details::ServiceResolvers();

			std::for_each(
				begin(_service_registerers), end(_service_registerers),
				[&service_resolvers](auto& registerer) { service_resolvers.merge(registerer->getServiceResolvers()); }
			);

			return Container(std::move(service_resolvers));
		}

	private:
		std::vector<std::shared_ptr<Details::ServiceRegisterer<>>> _service_registerers;
	};

	ContainerBuilder::ContainerBuilder()
		: _impl(std::make_unique<Impl>())
	{}

	ContainerBuilder::ContainerBuilder(ContainerBuilder&& other)
	{
		*this = std::forward<ContainerBuilder>(other);
	}

	ContainerBuilder::~ContainerBuilder()
	{}

	ContainerBuilder& ContainerBuilder::operator=(ContainerBuilder&& other)
	{
		std::swap(_impl, other._impl);

		return *this;
	}

	void ContainerBuilder::addRegisterer(std::shared_ptr<Details::ServiceRegisterer<>> registerer)
	{
		_impl->addRegisterer(registerer);
	}

	Container ContainerBuilder::build() const
	{
		return _impl->buildContainer();
	}

}