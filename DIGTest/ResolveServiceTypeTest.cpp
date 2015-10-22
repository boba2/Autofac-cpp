#include "ContainerBaseTest.h"
#include "../DI/Error/ServiceInstanceNotResolvableAs.h"

namespace
{
	struct DummyService {};
	struct AbstractDummyService { virtual ~AbstractDummyService() = 0; };
}

using ResolveRegisteredServiceTypeTest = ContainerBaseTest;

TEST_F(ResolveRegisteredServiceTypeTest, ShouldResolveServiceAsSharedPtr_WhenServiceTypeRegistered)
{
	builder().registerType<DummyService>();

	ASSERT_TRUE(dynamic_cast<DummyService*>(container().resolve<std::shared_ptr<DummyService>>().get()) != nullptr);
}

TEST_F(ResolveRegisteredServiceTypeTest, ShouldResolveServiceAsUniquePtr_WhenServiceTypeRegistered)
{
	builder().registerType<DummyService>();

	ASSERT_TRUE(dynamic_cast<DummyService*>(container().resolve<std::unique_ptr<DummyService>>().get()) != nullptr);
}

TEST_F(ResolveRegisteredServiceTypeTest, ShouldResolveServiceAsCopy_WhenNonAbstractServiceTypeRegistered)
{
	builder().registerType<DummyService>();

	auto service = container().resolve<DummyService>();

	ASSERT_TRUE(dynamic_cast<DummyService*>(&service) != nullptr);
}

TEST_F(ResolveRegisteredServiceTypeTest, ShouldBreakStaticAssert_WhenRegisteringAbstractServiceType)
{
//	builder().registerType<AbstractDummyService>();
}

TEST_F(ResolveRegisteredServiceTypeTest, ShouldThrowException_WhenResolvingServiceAsPointer_AndServiceTypeRegisteredNotAsAutoManageable)
{
	builder().registerType<DummyService>();

	ASSERT_THROW(container().resolve<DummyService*>(), DI::Error::ServiceInstanceNotResolvableAs);
}

TEST_F(ResolveRegisteredServiceTypeTest, ShouldThrowException_WhenResolvingServiceAsReference_AndServiceTypeRegisteredNotAsAutoManageable)
{
	builder().registerType<DummyService>();

	ASSERT_THROW(container().resolve<DummyService&>(), DI::Error::ServiceInstanceNotResolvableAs);
}