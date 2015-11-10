#include "ServiceResolvers.h"

#include <unordered_map>
#include <algorithm>

namespace DI
{
	namespace Details
	{

		class ServiceResolvers::Impl
		{
		public:
			void add(ServiceResolverCreatorPtr resolver_creator)
			{
				const auto& type_index = resolver_creator->getServiceType();
				auto resolver = resolver_creator->getServiceResolver();

				if (_service_resolvers.find(type_index) == end(_service_resolvers))
					_service_resolvers[type_index] = resolver_creator->createCompositeServiceResolver();

				_service_resolvers[type_index]->addResolver(resolver);
			}

			void merge(const Impl& other)
			{
				std::for_each(
					begin(other._service_resolvers), end(other._service_resolvers),
					[=](auto& resolver_it)
					{
						if (_service_resolvers.find(resolver_it.first) == end(_service_resolvers))
							_service_resolvers[resolver_it.first] = resolver_it.second;
						else
							_service_resolvers[resolver_it.first]->merge(*resolver_it.second);
					}
				);
			}

			auto empty() const -> bool
			{
				return _service_resolvers.empty();
			}

			auto get(TypeIndex type_index) const -> ServiceResolverPtr<>
			{
				auto resolver_it = _service_resolvers.find(type_index);
				if (resolver_it == end(_service_resolvers))
					return nullptr;

				return std::dynamic_pointer_cast<ServiceResolver<>>(resolver_it->second);
			}

		private:
			std::unordered_map<TypeIndex, CompositeServiceResolverPtr<>> _service_resolvers;
		};

		ServiceResolvers::ServiceResolvers()
			: _impl(std::make_unique<Impl>())
		{}

		ServiceResolvers::ServiceResolvers(ServiceResolvers&& other)
			: _impl(std::move(other._impl))
		{}

		ServiceResolvers::~ServiceResolvers()
		{}

		void ServiceResolvers::add(ServiceResolverCreatorPtr resolver)
		{
			_impl->add(resolver);
		}

		void ServiceResolvers::merge(const ServiceResolvers& other)
		{
			_impl->merge(*other._impl);
		}

		auto ServiceResolvers::empty() const -> bool
		{
			return _impl->empty();
		}

		auto ServiceResolvers::get(const TypeIndex& type_index) const -> ServiceResolverPtr<>
		{
			return _impl->get(type_index);
		}

	}
}