#include "Container.h"

#include "Details/ServiceFactoryRegisterer.h"
#include "Error/ServiceNotRegistered.h"
#include "Details/ServiceResolvers.h"
#include <algorithm>

namespace DI
{
	class Container::Impl : public std::enable_shared_from_this<Container::Impl>
	{
	public:
		explicit Impl(Details::ServiceResolvers service_resolvers)
			: _service_resolvers(std::move(service_resolvers))
		{
			registerContainer();
		}

		Details::ServiceResolver<> &getResolver(const Details::TypeIndex& type_index) const
		{
			auto resolver = _service_resolvers.get(type_index);

			if (!resolver)
				throw Error::ServiceNotRegistered();

			return *resolver;
		}

	private:
		void registerContainer()
		{
			auto container_factory = [=] { return std::make_shared<Container>(Container(this->shared_from_this())); };
			auto registerer = Details::ServiceFactoryRegisterer<decltype(container_factory)>(container_factory);
			registerer.setSingleInstance();

			_service_resolvers.merge(registerer.getServiceResolvers());
		}

	private:
		Details::ServiceResolvers _service_resolvers;
	};

	Container::Container()
	{
	}

	Container::Container(Details::ServiceResolvers service_resolvers)
		: _impl(std::make_unique<Impl>(std::move(service_resolvers)))
	{
	}

	Container::Container(std::shared_ptr<Impl> impl)
		: _impl(impl)
	{
	}

	Container::Container(const Container& other)
		: _impl(other._impl)
	{
	}

	Container& Container::operator=(const Container& other)
	{
		_impl = other._impl;

		return *this;
	}

	Details::ServiceResolver<> &Container::getResolver(const Details::TypeIndex& type_index) const
	{
		return _impl->getResolver(type_index);
	}

}
