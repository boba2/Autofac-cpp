#include "Container.h"

#include <set>
#include <unordered_map>
#include "Details/ServiceInstanceRegisterer.h"
#include "Error/ServiceNotRegistered.h"

namespace DI
{
	using namespace Details;

	class Container::Impl
	{
	public:
		explicit Impl(const std::set<std::shared_ptr<ServiceResolver<>>>& service_resolvers)
		{
			registerResolvers(service_resolvers);
		}

		ServiceResolver<> &getResolver(const TypeIndex<>& type_index) const
		{
			auto resolver_it = _service_resolvers.find(type_index);
			if (resolver_it == end(_service_resolvers))
				throw Error::ServiceNotRegistered();

			return *resolver_it->second;
		}

		void registerContainer(Container& container)
		{
			registerResolvers(ServiceInstanceRegisterer<Container>(container).getServiceResolvers());
		}

	private:
		void registerResolvers(const std::set<std::shared_ptr<ServiceResolver<>>>& service_resolvers)
		{
			for (auto &resolver : service_resolvers)
				_service_resolvers[resolver->getServiceType()] = resolver;
		}

	private:
		std::unordered_map<TypeIndex<>, std::shared_ptr<ServiceResolver<>>> _service_resolvers;
	};

	Container::Container()
	{
	}

	Container::Container(const std::set<std::shared_ptr<Details::ServiceResolver<>>>& service_resolvers)
		: _impl(std::make_unique<Impl>(service_resolvers))
	{	
		_impl->registerContainer(*this);
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

	ServiceResolver<> &Container::getResolver(const Details::TypeIndex<>& type_index) const
	{
		return _impl->getResolver(type_index);
	}

}
