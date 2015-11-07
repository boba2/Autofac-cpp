#pragma once

#include "ServiceRegisterer.h"

namespace DI
{

	class DI_API ContainerBuilder : public ServiceRegisterer
	{
	public:
		ContainerBuilder();

		Container build() const;
	};

}