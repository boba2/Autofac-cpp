#pragma once

#include "ContainerBuilder.h"
#include "Details/ServiceInstanceRegisterer.h"
#include "Details/ServiceTypeRegisterer.h"
#include "Details/ServiceFactoryRegisterer.h"

namespace DI
{

	class ContainerBuilder::Impl
	{
	public:
		void addRegisterer(std::shared_ptr<Details::ServiceRegisterer<>> registerer)
		{
			_service_registerers.insert(registerer);
		}

		auto getRegisterers() const
		{
			return _service_registerers;
		}

	private:
		std::set<std::shared_ptr<Details::ServiceRegisterer<>>> _service_registerers;
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
	auto ContainerBuilder::registerInstance(T &&instance) -> ServiceInstanceRegisterer<typename Details::UnderlyingType<T>::Type>
	{
		using Registerer = Details::ServiceInstanceRegisterer<T>;
		using PublicType = ServiceInstanceRegisterer<typename Details::UnderlyingType<T>::Type>;

		return createRegisterer<Registerer, PublicType>(std::forward<T>(instance));
	}

	template<class T>
	auto ContainerBuilder::registerType() -> ServiceTypeRegisterer<T>
	{
		using Registerer = Details::ServiceTypeRegisterer<T>;
		using PublicType = ServiceTypeRegisterer<T>;

		return createRegisterer<Registerer, PublicType>();
	}

	template<class T>
	auto ContainerBuilder::registerFactory(T factory) -> ServiceFactoryRegisterer<typename Details::UnderlyingType<typename Details::FunctionResultType<T>::Type>::Type>
	{
		using Registerer = Details::ServiceFactoryRegisterer<T>;
		using PublicType = ServiceFactoryRegisterer<typename Details::UnderlyingType<typename Details::FunctionResultType<T>::Type>::Type>;

		return createRegisterer<Registerer, PublicType>(factory);
	}

	template<class T, class S, class... U>
	auto ContainerBuilder::createRegisterer(U&&... param)
	{
		auto registerer = std::make_shared<T>(std::forward<U>(param)...);
		_impl->addRegisterer(registerer);

		return S(this, registerer);
	}

	inline auto ContainerBuilder::getServiceResolvers() const
	{
		auto result = std::vector<std::shared_ptr<Details::ServiceResolver<>>>();

		for (const auto& registerer : _impl->getRegisterers())
		{
			const auto& resolvers = registerer->getServiceResolvers();
			result.insert(end(result), begin(resolvers), end(resolvers));
		}

		return result;
	}

	inline Container ContainerBuilder::build() const
	{
		return Container(getServiceResolvers());
	}

}