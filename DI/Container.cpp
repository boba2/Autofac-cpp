#include "Container.h"

#include <set>
#include <unordered_map>
#include "Details/ServiceFactoryRegisterer.h"
#include "Error/ServiceNotRegistered.h"

namespace DI
{
	class Container::Impl : public std::enable_shared_from_this<Container::Impl>
	{
	public:
		explicit Impl(const std::vector<std::shared_ptr<Details::ServiceResolver<>>>& service_resolvers)
		{
			registerResolvers(service_resolvers);
			registerContainer();
		}

		Details::ServiceResolver<> &getResolver(const Details::TypeIndex<>& type_index) const
		{
			auto resolver_it = _service_resolvers.find(type_index);
			if (resolver_it == end(_service_resolvers))
				throw Error::ServiceNotRegistered();

			return *resolver_it->second;
		}

	private:
		void registerContainer()
		{
			auto container_factory = [this] { return std::make_shared<Container>(Container(this->shared_from_this())); };
			auto registerer = Details::ServiceFactoryRegisterer<decltype(container_factory)>(container_factory);
			registerer.setSingleInstance();
			registerResolvers(registerer.getServiceResolvers());
		}

		void registerResolvers(const std::vector<std::shared_ptr<Details::ServiceResolver<>>>& service_resolvers)
		{
			for (auto &resolver : service_resolvers)
				_service_resolvers[resolver->getServiceType()] = resolver;
		}

	private:
		std::unordered_map<Details::TypeIndex<>, std::shared_ptr<Details::ServiceResolver<>>> _service_resolvers;
	};

	Container::Container()
	{
	}

	Container::Container(const std::vector<std::shared_ptr<Details::ServiceResolver<>>>& service_resolvers)
		: _impl(std::make_unique<Impl>(service_resolvers))
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

	Container::~Container()
	{
	}

	Container& Container::operator=(const Container& other)
	{
		_impl = other._impl;

		return *this;
	}

	Details::ServiceResolver<> &Container::getResolver(const Details::TypeIndex<>& type_index) const
	{
		return _impl->getResolver(type_index);
	}

}
