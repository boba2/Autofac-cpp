#include "ContainerBuilder.h"

#include "Details/ServiceRegisterers.h"

namespace DI
{
	
	class ContainerBuilder::Impl
	{
	public:
		void addRegisterer(std::shared_ptr<Details::ServiceRegisterer<>> registerer)
		{
			_service_registerers.add(registerer);
		}

		void forEach(std::function<void(const Details::ServiceRegisterer<>&)> action) const
		{
			_service_registerers.forEach(action);
		}

	private:
		Details::ServiceRegisterers _service_registerers;
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
		auto service_resolvers = Details::ServiceResolvers();

		_impl->forEach([&service_resolvers](const Details::ServiceRegisterer<>& registerer)
		{
			service_resolvers.merge(registerer.getServiceResolvers());
		});

		return Container(std::move(service_resolvers));
	}

}