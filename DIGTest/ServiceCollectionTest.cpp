#include <stdafx.h>
#include "ContainerBaseTest.h"

using ServiceCollectionTest = ContainerBaseTest;

namespace
{
	struct Service { Service(int value) : _value(value) {} int const _value; };
}

TEST_F(ServiceCollectionTest, Should)
{
	builder()
		.registerInstance(Service(13))
		.registerInstance(Service(14));

	auto services = container().resolve<std::vector<std::shared_ptr<Service>>>();

	ASSERT_TRUE(services.size() == 2);
	ASSERT_EQ(13, services[0]->_value);
	ASSERT_EQ(14, services[1]->_value);
}