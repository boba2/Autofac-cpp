#include "ContainerBaseTest.h"
#include "../DITest/Error/ServiceInstanceNotResolvableAs.h"

struct DummyService {};
struct AbstractDummyService
{
	virtual ~AbstractDummyService() = 0;
};

TEST_F(ContainerBaseTest, ShouldResolveServiceBySharedPtr_WhenServiceTypeRegistered)
{
	builder().registerType<DummyService>();

	ASSERT_TRUE(dynamic_cast<DummyService*>(container().resolve<std::shared_ptr<DummyService>>().get()) != nullptr);
}

TEST_F(ContainerBaseTest, ShouldResolveServiceByUniquePtr_WhenServiceTypeRegistered)
{
	builder().registerType<DummyService>();

	ASSERT_TRUE(dynamic_cast<DummyService*>(container().resolve<std::unique_ptr<DummyService>>().get()) != nullptr);
}

TEST_F(ContainerBaseTest, ShouldResolveServiceByCopy_WhenNonAbstractServiceTypeRegistered)
{
	builder().registerType<DummyService>();

	auto service = container().resolve<DummyService>();

	ASSERT_TRUE(dynamic_cast<DummyService*>(&service) != nullptr);
}

TEST_F(ContainerBaseTest, ShouldThrowException_WhenResolvingServiceBySharedPtr_AndAbstractServiceTypeRegistered)
{
	builder().registerType<AbstractDummyService>();

	ASSERT_THROW(container().resolve<std::shared_ptr<AbstractDummyService>>(), DI::Error::ServiceInstanceNotResolvableAs);
}

TEST_F(ContainerBaseTest, ShouldThrowException_WhenResolvingServiceByUniquePtr_AndAbstractServiceTypeRegistered)
{
	builder().registerType<AbstractDummyService>();

	ASSERT_THROW(container().resolve<std::unique_ptr<AbstractDummyService>>(), DI::Error::ServiceInstanceNotResolvableAs);
}

TEST_F(ContainerBaseTest, ShouldThrowException_WhenResolvingServiceByCopy_AndAbstractServiceTypeRegistered)
{
	builder().registerType<AbstractDummyService>();

	ASSERT_THROW(container().resolve<AbstractDummyService>(), DI::Error::ServiceInstanceNotResolvableAs);
}

TEST_F(ContainerBaseTest, ShouldThrowException_WhenResolvingServiceByPointer_AndServiceTypeRegisteredNotAsAutoManageable)
{
	builder().registerType<DummyService>();

	ASSERT_THROW(container().resolve<DummyService*>(), DI::Error::ServiceInstanceNotResolvableAs);
}

TEST_F(ContainerBaseTest, ShouldThrowException_WhenResolvingServiceByReference_AndServiceTypeRegisteredNotAsAutoManageable)
{
	builder().registerType<DummyService>();

	ASSERT_THROW(container().resolve<DummyService&>(), DI::Error::ServiceInstanceNotResolvableAs);
}