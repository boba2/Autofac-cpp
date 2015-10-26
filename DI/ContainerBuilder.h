#pragma once

#include "Container.h"
#include "Details/ServiceInstanceRegisterer.h"
#include "Details/ServiceTypeRegisterer.h"
#include "Details/ServiceFactoryRegisterer.h"

namespace DI
{

	class ContainerBuilder
	{
	public:
		template<class T>
		auto registerInstance(T &&instance) -> typename Details::ServiceInstanceRegisterer<T>::PublicType
		{
			return createRegisterer<Details::ServiceInstanceRegisterer<T>>(std::forward<T>(instance));
		}

		template<class T>
		auto registerType() -> typename Details::ServiceTypeRegisterer<T>::PublicType
		{
			return createRegisterer<Details::ServiceTypeRegisterer<T>>();
		}

		template<class T>
		auto registerFactory(T factory) -> typename Details::ServiceFactoryRegisterer<T>::PublicType
		{
			return createRegisterer<Details::ServiceFactoryRegisterer<T>>(factory);
		}

		Container build() const
		{
			return Container(getServiceResolvers());
		}

	private:
		template<class T, class... U>
		auto createRegisterer(U&&... param)
		{
			auto registerer = std::make_shared<T>(std::forward<U>(param)...);
			_service_registerers.insert(registerer);

			return typename T::PublicType(this, registerer);
		}

		std::set<std::shared_ptr<Details::ServiceResolver<>>> getServiceResolvers() const
		{
			std::set<std::shared_ptr<Details::ServiceResolver<>>> result;

			for (const auto& registerer : _service_registerers)
			{
				const auto& resolvers = registerer->getServiceResolvers();
				result.insert(begin(resolvers), end(resolvers));
			}

			return result;
		}

	private:
		std::set<std::shared_ptr<Details::ServiceRegisterer<>>> _service_registerers;
	};

	template<class T>
	template<class U>
	auto ServiceRegisterer<T>::registerInstance(U &&instance)
	{
		return _container_builder->registerInstance(std::forward<U>(instance));
	}

	template<class T>
	template<class U>
	auto ServiceRegisterer<T>::registerType()
	{
		return _container_builder->registerType<U>();
	}

	template<class T>
	template<class U>
	auto ServiceRegisterer<T>::registerFactory(U factory)
	{
		return _container_builder->registerFactory(factory);
	}

	template<class T>
	Container ServiceRegisterer<T>::build() const
	{
		return _container_builder->build();
	}

}