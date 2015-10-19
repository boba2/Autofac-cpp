#include "ContainerBaseTest.h"

struct DummyService {};

using ResolveStandardServiceInstanceTest = ContainerBaseTest;

TEST_F(ResolveStandardServiceInstanceTest, ShouldResolveSameSingleServiceInstancefromDifferentContainerCopies)
{
//	builder().registerType<DummyService>().singleIntance();
//
//	auto container_copy = container().resolve<DI::Container>();
//
//	auto service1 = container().resolve<DummyService *>();
//	auto service2 = container_copy.resolve<DummyService *>();
//
//	ASSERT_EQ(service1, service2);
}

TEST_F(ResolveStandardServiceInstanceTest, ShouldResolveSameRegisteredServiceInstanceFromDifferentContainerCopies)
{
	builder().registerInstance(DummyService());

	auto container_copy = container().resolve<DI::Container>();

	auto service1 = container().resolve<DummyService *>();
	auto service2 = container_copy.resolve<DummyService *>();

	ASSERT_EQ(service1, service2);
}