#include "ContainerBuilder.h"

#include "Container.h"

namespace DI
{
	
	ContainerBuilder::ContainerBuilder()
		: ServiceRegisterer(*this)
	{}

	Container ContainerBuilder::build() const
	{
		return Container(std::move(getServiceResolvers()));
	}

}