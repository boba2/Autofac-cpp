#pragma once

#include "Details/Container.h"
#include "Details/ServiceInstanceRegisterer.h"

namespace DI
{

	class ContainerBuilder
	{
	public:
		template<class T>
		auto& registerInstance(T &&instance)
		{
			auto registerer = std::make_shared<Details::ServiceInstanceRegisterer<typename Details::UnderlyingType<T>::Type>>(std::forward<T>(instance));
			_service_registerers.insert(registerer);

			return *registerer;
		}

		std::unique_ptr<Details::Container> build() const
		{
			return std::make_unique<Details::Container>(getServiceResolvers());
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