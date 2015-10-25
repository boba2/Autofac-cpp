#include <stdafx.h>

#include "ContainerBaseTest.h"

namespace
{
	struct ServiceA {};
}

using StandardServiceInstanceTest = ContainerBaseTest;

TEST_F(StandardServiceInstanceTest, ShouldResolveContainerAsObject)
{
	auto service = container().resolve<DI::Container>();

	ASSERT_TRUE(dynamic_cast<DI::Container*>(&service) != nullptr);
}

TEST_F(StandardServiceInstanceTest, ShouldResolveContainerAsPtr)
{
	auto service = container().resolve<DI::Container*>();

	ASSERT_TRUE(dynamic_cast<DI::Container*>(service) != nullptr);
}

TEST_F(StandardServiceInstanceTest, ShouldResolveContainerAsRef)
{
	auto service = container().resolve<DI::Container&>();

	ASSERT_TRUE(dynamic_cast<DI::Container*>(&service) != nullptr);
}

TEST_F(StandardServiceInstanceTest, ShouldResolveContainerAsSharedPtr)
{
	auto service = container().resolve<std::shared_ptr<DI::Container>>();

	ASSERT_TRUE(dynamic_cast<DI::Container*>(service.get()) != nullptr);
}

TEST_F(StandardServiceInstanceTest, ShouldThrowException_WhenResolvingContainerAsUniquePtr)
{
	ASSERT_THROW(container().resolve<std::unique_ptr<DI::Container>>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(StandardServiceInstanceTest, ShouldResolveSameSingleServiceInstancefromDifferentContainerCopies)
{
	builder()
		.registerType<ServiceA>()
		.singleInstance();

	auto container_copy = container().resolve<std::shared_ptr<DI::Container>>();

	auto service1 = container().resolve<ServiceA *>();
	auto service2 = container_copy->resolve<ServiceA *>();

	ASSERT_EQ(service1, service2);
}

TEST_F(StandardServiceInstanceTest, ShouldResolveSameRegisteredServiceInstanceFromDifferentContainerCopies)
{
	builder().registerInstance(ServiceA());
	auto container_copy = container().resolve<std::shared_ptr<DI::Container>>();

	auto service1 = container().resolve<ServiceA *>();
	auto service2 = container_copy->resolve<ServiceA *>();

	ASSERT_EQ(service1, service2);
}