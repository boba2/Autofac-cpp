#include "ContainerBaseTest.h"

namespace
{
	struct DummyService { int _value; };
	struct DummyService1 { virtual ~DummyService1() {} };
	struct DummyService2 { virtual ~DummyService2() {} };
	struct SpecialDummyService : DummyService1, DummyService2 {};
}

using ResolveServiceTypeAsSingleInstance = ContainerBaseTest;

TEST_F(ResolveServiceTypeAsSingleInstance, ShouldResolveSingleServiceByPtr_WhenServiceTypeRegisteredAsSingleInstance)
{
	builder()
		.registerType<DummyService>()
		.singleInstance();

	auto service1 = container().resolve<DummyService*>();
	auto service2 = container().resolve<DummyService*>();

	ASSERT_EQ(service1, service2);
}

TEST_F(ResolveServiceTypeAsSingleInstance, ShouldResolveSingleServiceByRef_WhenServiceTypeRegisteredAsSingleInstance)
{
	builder()
		.registerType<DummyService>()
		.singleInstance();

	auto& service1 = container().resolve<DummyService&>();
	auto& service2 = container().resolve<DummyService&>();

	ASSERT_EQ(&service1, &service2);
}

TEST_F(ResolveServiceTypeAsSingleInstance, ShouldResolveSingleServiceBySharedPtr_WhenServiceTypeRegisteredAsSingleInstance)
{
	builder()
		.registerType<SpecialDummyService>()
		.singleInstance();

	auto service1 = container().resolve<std::shared_ptr<SpecialDummyService>>();
	auto service2 = container().resolve<std::shared_ptr<SpecialDummyService>>();

	ASSERT_EQ(service1, service2);
}

TEST_F(ResolveServiceTypeAsSingleInstance, ShouldThrowException_WhenResolvingSingleServiceByUniquePtr)
{
	builder()
		.registerType<SpecialDummyService>()
		.singleInstance();

	ASSERT_THROW(container().resolve<std::unique_ptr<SpecialDummyService>>(), DI::Error::ServiceInstanceNotResolvableAs);
}

TEST_F(ResolveServiceTypeAsSingleInstance, ShouldResolveSingleServiceByCopy_WhenServiceTypeRegisteredAsSingleInstance)
{
	builder()
		.registerType<DummyService>()
		.singleInstance();

	container().resolve<DummyService*>()->_value = 13;
	auto service = container().resolve<DummyService>();

	ASSERT_EQ(13, service._value);
}

TEST_F(ResolveServiceTypeAsSingleInstance, ShouldResolveSingleServiceByBaseType_WhenServiceTypeRegisteredAliasedAsBaseType_AndAsSingleInstance)
{
	builder()
		.registerType<SpecialDummyService>()
		.as<DummyService1>()
		.as<DummyService2>()
		.singleInstance();

	auto service1 = container().resolve<std::shared_ptr<DummyService1>>();
	auto service2 = container().resolve<std::shared_ptr<DummyService2>>();

	ASSERT_EQ(std::dynamic_pointer_cast<SpecialDummyService>(service1), std::dynamic_pointer_cast<SpecialDummyService>(service2));
}