#include <stdafx.h>

#include "ContainerBaseTest.h"
#include "../DI/Error/ServiceNotResolvableAs.h"

namespace
{
	struct DummyService {};
	struct AbstractDummyService { virtual ~AbstractDummyService() = 0; };
}

using ServiceTypeTest = ContainerBaseTest;

TEST_F(ServiceTypeTest, ShouldBreakStaticAssert_WhenRegisteringAbstractServiceType)
{
//	builder().registerType<AbstractDummyService>();
}

TEST_F(ServiceTypeTest, ShouldBreakStaticAssert_WhenRegisteringServiceOfDecoratedType)
{
//	builder().registerType<DummyService*>();
}

TEST_F(ServiceTypeTest, ShouldResolveServiceAsCopy_WhenNonAbstractServiceTypeRegistered)
{
	builder()
		.registerType<DummyService>();

	auto service = container().resolve<DummyService>();

	ASSERT_TRUE(dynamic_cast<DummyService*>(&service) != nullptr);
}

TEST_F(ServiceTypeTest, ShouldThrowException_WhenResolvingServiceAsReference_AndServiceTypeRegisteredNotAsAutoManaged)
{
	builder()
		.registerType<DummyService>();

	ASSERT_THROW(container().resolve<DummyService&>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceTypeTest, ShouldResolveServiceAsReference_WhenServiceTypeRegisteredAsAutoManaged)
{
	builder()
		.registerType<DummyService>()
		.autoManaged();

	auto& service = container().resolve<DummyService&>();

	ASSERT_TRUE(dynamic_cast<DummyService*>(&service) != nullptr);
}

TEST_F(ServiceTypeTest, ShouldResolveServicesAsDistinctReferences_WhenServiceTypeRegisteredAsAutoManaged)
{
	builder()
		.registerType<DummyService>()
		.autoManaged();

	auto& service1 = container().resolve<DummyService&>();
	auto& service2 = container().resolve<DummyService&>();

	ASSERT_NE(&service1, &service2);
}

TEST_F(ServiceTypeTest, ShouldThrowException_WhenResolvingServiceAsPointer_AndServiceTypeRegisteredNotAsAutoManaged)
{
	builder()
		.registerType<DummyService>();

	ASSERT_THROW(container().resolve<DummyService*>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceTypeTest, ShouldResolveServiceAsPointer_WhenServiceTypeRegisteredAsAutoManageable)
{
	builder()
		.registerType<DummyService>()
		.autoManaged();

	ASSERT_TRUE(container().resolve<DummyService*>() != nullptr);
}

TEST_F(ServiceTypeTest, ShouldResolveServicesAsDistinctPointers_WhenServiceTypeRegisteredAsAutoManageable)
{
	builder()
		.registerType<DummyService>()
		.autoManaged();

	auto service1 = container().resolve<DummyService*>();
	auto service2 = container().resolve<DummyService*>();

	ASSERT_NE(service1, service2);
}

TEST_F(ServiceTypeTest, ShouldResolveServiceAsSharedPtr_WhenServiceTypeRegistered)
{
	builder()
		.registerType<DummyService>();

	ASSERT_TRUE(dynamic_cast<DummyService*>(container().resolve<std::shared_ptr<DummyService>>().get()) != nullptr);
}

TEST_F(ServiceTypeTest, ShouldResolveServiceAsUniquePtr_WhenServiceTypeRegistered)
{
	builder()
		.registerType<DummyService>();

	ASSERT_TRUE(dynamic_cast<DummyService*>(container().resolve<std::unique_ptr<DummyService>>().get()) != nullptr);
}