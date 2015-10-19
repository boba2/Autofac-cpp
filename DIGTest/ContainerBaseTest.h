#pragma once

#include <gtest/gtest.h>
#include "../DI/Container.h"
#include "../DI/ContainerBuilder.h"

struct ContainerBaseTest : ::testing::Test
{
	DI::ContainerBuilder &builder()
	{
		return _container_builder;
	}

	DI::Container &container()
	{
		if (!_container_valid)
		{
			_container = _container_builder.build();
			_container_valid = true;
		}

		return _container;
	}

	DI::ContainerBuilder _container_builder;
	DI::Container _container;
	bool _container_valid = false;
};
