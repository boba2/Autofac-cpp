#include <stdafx.h>

#include "ContainerBaseTest.h"

using ContainerBuilderUsageTest = ContainerBaseTest;

namespace
{
	struct ServiceA {};
	struct ServiceB {};
}

TEST_F(ContainerBuilderUsageTest, ShouldRegisterDifferentServiceTypes_WhenRegisterMethodsChained)
{
	builder()
		.registerType<ServiceA>()
		.registerType<ServiceB>();

	auto serviceA = container().resolve<ServiceA>();
	auto serviceB = container().resolve<ServiceB>();

	ASSERT_TRUE(dynamic_cast<ServiceA*>(&serviceA) != nullptr);
	ASSERT_TRUE(dynamic_cast<ServiceB*>(&serviceB) != nullptr);
}

TEST_F(ContainerBuilderUsageTest, ShouldRegisterDifferentServiceFactories_WhenRegisterMethodsChained)
{
	builder()
		.registerFactory([] { return ServiceA(); })
		.registerFactory([] { return ServiceB(); });

	auto serviceA = container().resolve<ServiceA>();
	auto serviceB = container().resolve<ServiceB>();

	ASSERT_TRUE(dynamic_cast<ServiceA*>(&serviceA) != nullptr);
	ASSERT_TRUE(dynamic_cast<ServiceB*>(&serviceB) != nullptr);
}

TEST_F(ContainerBuilderUsageTest, ShouldRegisterDifferentServiceInstances_WhenRegisterMethodsChained)
{
	builder()
		.registerInstance(ServiceA())
		.registerInstance(ServiceB());

	auto serviceA = container().resolve<ServiceA>();
	auto serviceB = container().resolve<ServiceB>();

	ASSERT_TRUE(dynamic_cast<ServiceA*>(&serviceA) != nullptr);
	ASSERT_TRUE(dynamic_cast<ServiceB*>(&serviceB) != nullptr);
}

TEST_F(ContainerBuilderUsageTest, ShouldRegisterServicesWithDifferentDefinitions_WhenRegisterMethodsChained_1)
{
	builder()
		.registerInstance(ServiceA())
		.registerType<ServiceB>();

	auto serviceA = container().resolve<ServiceA>();
	auto serviceB = container().resolve<ServiceB>();

	ASSERT_TRUE(dynamic_cast<ServiceA*>(&serviceA) != nullptr);
	ASSERT_TRUE(dynamic_cast<ServiceB*>(&serviceB) != nullptr);
}

TEST_F(ContainerBuilderUsageTest, ShouldRegisterServicesWithDifferentDefinitions_WhenRegisterMethodsChained_2)
{
	builder()
		.registerType<ServiceA>()
		.registerFactory([] { return ServiceB(); });

	auto serviceA = container().resolve<ServiceA>();
	auto serviceB = container().resolve<ServiceB>();

	ASSERT_TRUE(dynamic_cast<ServiceA*>(&serviceA) != nullptr);
	ASSERT_TRUE(dynamic_cast<ServiceB*>(&serviceB) != nullptr);
}

TEST_F(ContainerBuilderUsageTest, ShouldRegisterServicesWithDifferentDefinitions_WhenRegisterMethodsChained_3)
{
	builder()
		.registerFactory([] { return ServiceA(); })
		.registerInstance(ServiceB());

	auto serviceA = container().resolve<ServiceA>();
	auto serviceB = container().resolve<ServiceB>();

	ASSERT_TRUE(dynamic_cast<ServiceA*>(&serviceA) != nullptr);
	ASSERT_TRUE(dynamic_cast<ServiceB*>(&serviceB) != nullptr);
}

TEST_F(ContainerBuilderUsageTest, ShouldRegisterDifferentServiceTypes_WhenRegisterMethodsChained_AndDifferentOptionsSpecified)
{
	builder()
		.registerType<ServiceA>()
			.singleInstance()
		.registerType<ServiceB>()
			.autoManaged();
		
	auto serviceA1 = container().resolve<ServiceA*>();
	auto serviceA2 = container().resolve<ServiceA*>();
	auto serviceB1 = container().resolve<ServiceB*>();
	auto serviceB2 = container().resolve<ServiceB*>();

	ASSERT_EQ(serviceA1, serviceA2);
	ASSERT_NE(serviceB1, serviceB2);
}

TEST_F(ContainerBuilderUsageTest, ShouldBuildContainer_WhenBuildMethodChainedToTypeRegistration)
{
	auto container = builder()
		.registerType<ServiceA>()
		.registerType<ServiceB>()
		.build();

	auto serviceA = container.resolve<ServiceA>();
	auto serviceB = container.resolve<ServiceB>();

	ASSERT_TRUE(dynamic_cast<ServiceA*>(&serviceA) != nullptr);
	ASSERT_TRUE(dynamic_cast<ServiceB*>(&serviceB) != nullptr);
}