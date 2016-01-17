#include <stdafx.h>

#include "ContainerBaseTest.h"
#include "../DI/Error/ServiceNotResolvableAs.h"

namespace
{
	struct Service {};
	struct AbstractService { virtual ~AbstractService() = 0; };
}

using ServiceTypeTest = ContainerBaseTest;

TEST_F(ServiceTypeTest, ShouldResolveServiceAsCopy_WhenNonAbstractServiceTypeRegistered)
{
	builder()
		.registerType<Service>();

	auto service = container().resolve<Service>();

	ASSERT_TRUE(isOfType<Service>(service));
}

TEST_F(ServiceTypeTest, ShouldThrowException_WhenResolvingServiceAsReference_AndServiceTypeRegisteredNotAsAutoManaged)
{
	builder()
		.registerType<Service>();

	ASSERT_THROW(container().resolve<Service&>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceTypeTest, ShouldResolveServiceAsReference_WhenServiceTypeRegisteredAsAutoManaged)
{
	builder()
		.registerType<Service>()
		.autoManaged();

	auto& service = container().resolve<Service&>();

	ASSERT_TRUE(isOfType<Service>(service));
}

TEST_F(ServiceTypeTest, ShouldResolveServicesAsDistinctReferences_WhenServiceTypeRegisteredAsAutoManaged)
{
	builder()
		.registerType<Service>()
		.autoManaged();

	auto& service1 = container().resolve<Service&>();
	auto& service2 = container().resolve<Service&>();

	ASSERT_NE(&service1, &service2);
}

TEST_F(ServiceTypeTest, ShouldThrowException_WhenResolvingServiceAsPointer_AndServiceTypeRegisteredNotAsAutoManaged)
{
	builder()
		.registerType<Service>();

	ASSERT_THROW(container().resolve<Service*>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceTypeTest, ShouldResolveServiceAsPointer_WhenServiceTypeRegisteredAsAutoManageable)
{
	builder()
		.registerType<Service>()
		.autoManaged();

	ASSERT_TRUE(container().resolve<Service*>() != nullptr);
}

TEST_F(ServiceTypeTest, ShouldResolveServicesAsDistinctPointers_WhenServiceTypeRegisteredAsAutoManageable)
{
	builder()
		.registerType<Service>()
		.autoManaged();

	auto service1 = container().resolve<Service*>();
	auto service2 = container().resolve<Service*>();

	ASSERT_NE(service1, service2);
}

TEST_F(ServiceTypeTest, ShouldResolveServiceAsSharedPtr_WhenServiceTypeRegistered)
{
	builder()
		.registerType<Service>();

	ASSERT_TRUE(dynamic_cast<Service*>(container().resolve<std::shared_ptr<Service>>().get()) != nullptr);
}

TEST_F(ServiceTypeTest, ShouldResolveServiceAsUniquePtr_WhenServiceTypeRegistered)
{
	builder()
		.registerType<Service>();

	ASSERT_TRUE(dynamic_cast<Service*>(container().resolve<std::unique_ptr<Service>>().get()) != nullptr);
}