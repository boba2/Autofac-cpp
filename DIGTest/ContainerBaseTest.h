#pragma once

#include <gtest/gtest.h>
#include "../DITest/Container.h"
#include "../DITest/ContainerBuilder.h"

struct ContainerBaseTest : ::testing::Test
{
	DI::ContainerBuilder &builder() const
	{
		return *_container_builder.get();
	}

	DI::Container &container()
	{
		return *(_container ? _container : _container = builder().build()).get();
	}

	std::unique_ptr<DI::ContainerBuilder> _container_builder = std::make_unique<DI::ContainerBuilder>();
	std::unique_ptr<DI::Container> _container;
};
