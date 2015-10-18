#include "ContainerBaseTest.h"
#include "../DITest/Error/ServiceInstanceNotResolvableAs.h"

struct DummyService
{
	virtual ~DummyService() {}
	virtual void doSomething() {} 
};
struct SpecialDummyService : DummyService {};

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

TEST_F(ContainerBaseTest, ShouldResolveServiceByCopy_WhenServiceTypeRegistered)
{
	builder().registerType<DummyService>();

	ASSERT_THROW(container().resolve<DummyService>(), DI::Error::ServiceInstanceNotResolvableAs);
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