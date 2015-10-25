#include <stdafx.h>

#include "ContainerBaseTest.h"

namespace
{
	struct DummyService {};
}

using StandardServiceInstanceTest = ContainerBaseTest;

TEST_F(StandardServiceInstanceTest, ShouldResolveSameSingleServiceInstancefromDifferentContainerCopies)
{
	builder()
		.registerType<DummyService>()
		.singleInstance();

	auto container_copy = container().resolve<std::shared_ptr<DI::Container>>();

	auto service1 = container().resolve<DummyService *>();
	auto service2 = container_copy->resolve<DummyService *>();

	ASSERT_EQ(service1, service2);
}

TEST_F(StandardServiceInstanceTest, ShouldResolveSameRegisteredServiceInstanceFromDifferentContainerCopies)
{
	builder().registerInstance(DummyService());
	auto container_copy = container().resolve<std::shared_ptr<DI::Container>>();

	auto service1 = container().resolve<DummyService *>();
	auto service2 = container_copy->resolve<DummyService *>();

	ASSERT_EQ(service1, service2);
}