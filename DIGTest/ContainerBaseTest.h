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

	template<class A, class B>
	bool isOfType(const B& service, std::enable_if_t<!std::is_pointer<B>::value>* = nullptr)
	{
		return dynamic_cast<const A*>(&service) != nullptr;
	}

	template<class A, class B>
	bool isOfType(const B& service, std::enable_if_t<std::is_pointer<B>::value>* = nullptr)
	{
		return dynamic_cast<const A*>(service) != nullptr;
	}

	DI::ContainerBuilder _container_builder;
	DI::Container _container;
	bool _container_valid = false;
};
