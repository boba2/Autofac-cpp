#pragma once

#include "ContainerBuilder.h"
#include "Details/ServiceInstanceRegisterer.h"
#include "Details/ServiceTypeRegisterer.h"
#include "Details/ServiceFactoryRegisterer.h"
#include "Container.h"
#include "Details/ServiceResolvers.h"

namespace DI
{

	class ContainerBuilder::Impl
	{
	public:
		void addRegisterer(std::shared_ptr<Details::ServiceRegisterer<>> registerer)
		{
			_service_registerers.push_back(registerer);
		}

		auto getRegisterers() const
		{
			return _service_registerers;
		}

	private:
		std::vector<std::shared_ptr<Details::ServiceRegisterer<>>> _service_registerers;
	};

	inline ContainerBuilder::ContainerBuilder()
		: _impl(std::make_unique<Impl>())
	{}

	inline ContainerBuilder::ContainerBuilder(ContainerBuilder&& other)
	{
		*this = std::forward<ContainerBuilder>(other);
	}

	inline ContainerBuilder::~ContainerBuilder()
	{}

	inline ContainerBuilder& ContainerBuilder::operator=(ContainerBuilder&& other)
	{
		std::swap(_impl, other._impl);

		return *this;
	}

	template<class T>
	auto ContainerBuilder::registerInstance(T &&instance) -> ServiceInstanceRegisterer<T>
	{
		return createRegisterer<Details::ServiceInstanceRegisterer<T>, ServiceInstanceRegisterer<T>>(std::forward<T>(instance));
	}

	template<class T>
	auto ContainerBuilder::registerType() -> ServiceTypeRegisterer<T>
	{
		return createRegisterer<Details::ServiceTypeRegisterer<T>, ServiceTypeRegisterer<T>>();
	}

	template<class T>
	auto ContainerBuilder::registerFactory(T factory) -> ServiceFactoryRegisterer<T>
	{
		return createRegisterer<Details::ServiceFactoryRegisterer<T>, ServiceFactoryRegisterer<T>>(factory);
	}

	template<class T, class S, class... U>
	auto ContainerBuilder::createRegisterer(U&&... param)
	{
		auto registerer = std::make_shared<T>(std::forward<U>(param)...);
		_impl->addRegisterer(registerer);

		return S(registerer, this);
	}

	inline auto ContainerBuilder::getServiceResolvers() const
	{
		auto result = Details::ServiceResolvers();

		for (const auto& registerer : _impl->getRegisterers())
			result.merge(registerer->getServiceResolvers());

		return result;
	}

	inline Container ContainerBuilder::build() const
	{
		return Container(getServiceResolvers());
	}

}