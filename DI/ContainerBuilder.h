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
		auto registerInstance(T &&instance) -> ServiceRegisterer<typename Details::UnderlyingType<T>::Type>&
		{
			auto registerer = std::make_shared<Details::ServiceInstanceRegisterer<typename Details::UnderlyingType<T>::Type>>(std::forward<T>(instance));
			_service_registerers.insert(registerer);

			return *registerer;
		}

		template<class T>
		auto registerType() -> ServiceTypeRegisterer<typename Details::UnderlyingType<T>::Type>&
		{
			auto registerer = std::make_shared<Details::ServiceTypeRegisterer<T>>();
			_service_registerers.insert(registerer);

			return *registerer;
		}

		template<class T>
		void registerFactory(T factory)
		{
			auto registerer = std::make_shared<Details::ServiceFactoryRegisterer<typename Details::UnderlyingType<decltype(factory())>::Type>>(factory);
			_service_registerers.insert(registerer);
		}

		Container build() const
		{
			return Container(getServiceResolvers());
		}

	private:
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

}