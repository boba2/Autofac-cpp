#include <stdafx.h>

#include "ContainerBaseTest.h"

namespace
{
	struct ServiceA { int _value; };
	struct ServiceB { virtual ~ServiceB() {} };
	struct ServiceC { virtual ~ServiceC() {} };
	struct SpecialService : ServiceB, ServiceC {};
}

using ServiceTypeAsSingleInstance = ContainerBaseTest;

TEST_F(ServiceTypeAsSingleInstance, ShouldResolveSingleServiceAsPtr_WhenServiceTypeRegisteredAsSingleInstance)
{
	builder()
		.registerType<ServiceA>()
		.singleInstance();

	auto service1 = container().resolve<ServiceA*>();
	auto service2 = container().resolve<ServiceA*>();

	ASSERT_EQ(service1, service2);
}

TEST_F(ServiceTypeAsSingleInstance, ShouldResolveSingleServiceAsRef_WhenServiceTypeRegisteredAsSingleInstance)
{
	builder()
		.registerType<ServiceA>()
		.singleInstance();

	auto& service1 = container().resolve<ServiceA&>();
	auto& service2 = container().resolve<ServiceA&>();

	ASSERT_EQ(&service1, &service2);
}

TEST_F(ServiceTypeAsSingleInstance, ShouldResolveSingleServiceAsSharedPtr_WhenServiceTypeRegisteredAsSingleInstance)
{
	builder()
		.registerType<ServiceA>()
		.singleInstance();

	auto service1 = container().resolve<std::shared_ptr<ServiceA>>();
	auto service2 = container().resolve<std::shared_ptr<ServiceA>>();

	ASSERT_EQ(service1, service2);
}

TEST_F(ServiceTypeAsSingleInstance, ShouldThrowException_WhenResolvingSingleServiceAsUniquePtr)
{
	builder()
		.registerType<ServiceA>()
		.singleInstance();

	ASSERT_THROW(container().resolve<std::unique_ptr<ServiceA>>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceTypeAsSingleInstance, ShouldResolveSingleServiceAsCopy_WhenServiceTypeRegisteredAsSingleInstance)
{
	builder()
		.registerType<ServiceA>()
		.singleInstance();

	container().resolve<ServiceA*>()->_value = 13;
	auto service = container().resolve<ServiceA>();

	ASSERT_EQ(13, service._value);
}

TEST_F(ServiceTypeAsSingleInstance, ShouldResolveSingleServiceAsBaseType_WhenServiceTypeRegisteredAliasedAsBaseType_AndAsSingleInstance)
{
	builder()
		.registerType<SpecialService>()
		.as<ServiceB>()
		.as<ServiceC>()
		.singleInstance();

	auto service1 = container().resolve<ServiceB*>();
	auto service2 = container().resolve<ServiceC*>();

	ASSERT_EQ(dynamic_cast<SpecialService*>(service1), dynamic_cast<SpecialService*>(service2));
}