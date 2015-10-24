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
		auto registerInstance(T &&instance)
		{
			return createRegisterer<Details::ServiceInstanceRegisterer<T>>(std::forward<T>(instance));
		}

		template<class T>
		auto registerType()
		{
			return createRegisterer<Details::ServiceTypeRegisterer<T>>();
		}

		template<class T>
		auto registerFactory(T factory)
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

			return static_cast<typename T::PublicType>(registerer);
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

}