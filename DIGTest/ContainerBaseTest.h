#pragma once
#include "../DITest/Container.h"
#include "../DITest/ContainerBuilder.h"
#include <gtest/gtest.h>

struct ContainerBaseTest : ::testing::Test
{
	ContainerBuilder *builder() const
	{
		return _container_builder.get();
	}

	Container *container()
	{
		return (_container ? _container : _container = builder()->build()).get();
	}

	std::unique_ptr<ContainerBuilder> _container_builder = std::make_unique<ContainerBuilder>();
	std::unique_ptr<Container> _container;
};
