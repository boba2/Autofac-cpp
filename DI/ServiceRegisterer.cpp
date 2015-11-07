#include "ServiceRegisterer.h"

#include "ContainerBuilder.h"
#include "Container.h"

namespace DI
{

	Container ServiceRegisterer::build() const
	{
		return _container_builder.build();
	}

}