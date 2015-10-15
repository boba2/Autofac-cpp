#include <gtest/gtest.h>
#include "../DITest/ContainerBuilder.h"

struct ResolveStandardServiceInstanceTest : ::testing::Test
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

TEST_F(ResolveStandardServiceInstanceTest, container)
{
	auto c = container();
	auto c2 = c->resolve<Container *>();
	ASSERT_EQ(c, c2);
}