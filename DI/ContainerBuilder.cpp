#include <stdafx.h>

#include "ContainerBuilder.h"

namespace DI
{

	auto ContainerBuilder::getServiceResolvers() const
	{
		std::set<std::shared_ptr<Details::ServiceResolver<>>> result;

		for (const auto& registerer : _service_registerers)
		{
			const auto& resolvers = registerer->getServiceResolvers();
			result.insert(begin(resolvers), end(resolvers));
		}

		return result;
	}

	Container ContainerBuilder::build() const
	{
		return Container(getServiceResolvers());
	}

}