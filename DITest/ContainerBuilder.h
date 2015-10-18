#pragma once

#include "Container.h"
#include "ServiceInstanceRegisterer.h"
#include <algorithm>
#include <iterator>

namespace DI
{

	class ContainerBuilder
	{
	public:
		template<class T>
		void registerInstance(T &&instance)
		{
			_service_registerers.insert(std::make_shared<Details::ServiceInstanceRegisterer<typename Details::UnderlyingType<T>::Type>>(std::forward<T>(instance)));
		}

		std::unique_ptr<Container> build() const
		{
			return std::make_unique<Container>(getServiceResolvers());
		}

	private:
		std::set<std::shared_ptr<Details::ServiceResolver<>>> getServiceResolvers() const
		{
			std::set<std::shared_ptr<Details::ServiceResolver<>>> result;

			std::transform(
				begin(_service_registerers),
				end(_service_registerers),
				inserter(result, begin(result)),
				[](auto registerer) { return registerer->getServiceResolver(); }
			);

			return result;
		}

	private:
		std::set<std::shared_ptr<Details::ServiceRegisterer<>>> _service_registerers;
	};

}