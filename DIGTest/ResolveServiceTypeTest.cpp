#include "ContainerBaseTest.h"
#include "../DI/Error/ServiceNotResolvableAs.h"
#include "../DI/Error/BadServiceDefinition.h"

namespace
{
	struct DummyService {};
	struct AbstractDummyService { virtual ~AbstractDummyService() = 0; };
}

using ResolveRegisteredServiceTypeTest = ContainerBaseTest;

TEST_F(ResolveRegisteredServiceTypeTest, ShouldThrowException_WhenRegisteringAbstractServiceType)
{
	ASSERT_THROW(builder().registerType<AbstractDummyService>(), DI::Error::BadServiceDefinition);
}

TEST_F(ResolveRegisteredServiceTypeTest, ShouldResolveServiceAsCopy_WhenNonAbstractServiceTypeRegistered)
{
	builder()
		.registerType<DummyService>();

	auto service = container().resolve<DummyService>();

	ASSERT_TRUE(dynamic_cast<DummyService*>(&service) != nullptr);
}

TEST_F(ResolveRegisteredServiceTypeTest, ShouldThrowException_WhenResolvingServiceAsReference_AndServiceTypeRegisteredNotAsAutoManaged)
{
	builder()
		.registerType<DummyService>();

	ASSERT_THROW(container().resolve<DummyService&>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ResolveRegisteredServiceTypeTest, ShouldResolveServiceAsReference_WhenServiceTypeRegisteredAsAutoManaged)
{
	builder()
		.registerType<DummyService>()
		.autoManaged();

	auto& service = container().resolve<DummyService&>();

	ASSERT_TRUE(dynamic_cast<DummyService*>(&service) != nullptr);
}

TEST_F(ResolveRegisteredServiceTypeTest, ShouldThrowException_WhenResolvingServiceAsPointer_AndServiceTypeRegisteredNotAsAutoManaged)
{
	builder()
		.registerType<DummyService>();

	ASSERT_THROW(container().resolve<DummyService*>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ResolveRegisteredServiceTypeTest, ShouldResolveServiceAsPointer_WhenServiceTypeRegisteredAsAutoManageable)
{
	builder()
		.registerType<DummyService>()
		.autoManaged();

	ASSERT_TRUE(container().resolve<DummyService*>() != nullptr);
}

TEST_F(ResolveRegisteredServiceTypeTest, ShouldResolveServiceAsSharedPtr_WhenServiceTypeRegistered)
{
	builder()
		.registerType<DummyService>();

	ASSERT_TRUE(dynamic_cast<DummyService*>(container().resolve<std::shared_ptr<DummyService>>().get()) != nullptr);
}

TEST_F(ResolveRegisteredServiceTypeTest, ShouldResolveServiceAsUniquePtr_WhenServiceTypeRegistered)
{
	builder()
		.registerType<DummyService>();

	ASSERT_TRUE(dynamic_cast<DummyService*>(container().resolve<std::unique_ptr<DummyService>>().get()) != nullptr);
}