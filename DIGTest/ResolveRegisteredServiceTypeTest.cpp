#include "ContainerBaseTest.h"
#include "../DI/Error/ServiceInstanceNotResolvableAs.h"

struct DummyService {};
struct AbstractDummyService
{
	virtual ~AbstractDummyService() = 0;
};

using ResolveRegisteredServiceTypeTest = ContainerBaseTest;

TEST_F(ResolveRegisteredServiceTypeTest, ShouldResolveServiceBySharedPtr_WhenServiceTypeRegistered)
{
	builder().registerType<DummyService>();

	ASSERT_TRUE(dynamic_cast<DummyService*>(container().resolve<std::shared_ptr<DummyService>>().get()) != nullptr);
}

TEST_F(ResolveRegisteredServiceTypeTest, ShouldResolveServiceByUniquePtr_WhenServiceTypeRegistered)
{
	builder().registerType<DummyService>();

	ASSERT_TRUE(dynamic_cast<DummyService*>(container().resolve<std::unique_ptr<DummyService>>().get()) != nullptr);
}

TEST_F(ResolveRegisteredServiceTypeTest, ShouldResolveServiceByCopy_WhenNonAbstractServiceTypeRegistered)
{
	builder().registerType<DummyService>();

	auto service = container().resolve<DummyService>();

	ASSERT_TRUE(dynamic_cast<DummyService*>(&service) != nullptr);
}

TEST_F(ResolveRegisteredServiceTypeTest, ShouldBreakStaticAssert_WhenRegisteringAbstractServiceType)
{
//	builder().registerType<AbstractDummyService>();
}

TEST_F(ResolveRegisteredServiceTypeTest, ShouldThrowException_WhenResolvingServiceByPointer_AndServiceTypeRegisteredNotAsAutoManageable)
{
	builder().registerType<DummyService>();

	ASSERT_THROW(container().resolve<DummyService*>(), DI::Error::ServiceInstanceNotResolvableAs);
}

TEST_F(ResolveRegisteredServiceTypeTest, ShouldThrowException_WhenResolvingServiceByReference_AndServiceTypeRegisteredNotAsAutoManageable)
{
	builder().registerType<DummyService>();

	ASSERT_THROW(container().resolve<DummyService&>(), DI::Error::ServiceInstanceNotResolvableAs);
}