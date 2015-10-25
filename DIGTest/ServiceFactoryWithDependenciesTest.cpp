#include <stdafx.h>

#include "ContainerBaseTest.h"

using ServiceFactoryWithDependenciesTest = ContainerBaseTest;

namespace
{
	struct ServiceA { int _value; };
	struct ServiceB { explicit ServiceB(ServiceA serviceA) : _serviceA(serviceA) {} ServiceA _serviceA; };
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactory_WhenFactoryRequiresOneServiceAsObject)
{
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 13; return serviceA; });
	builder()
		.registerFactory([](ServiceA serviceA) { return ServiceB(serviceA); });

	auto serviceB = container().resolve<ServiceB>();

	ASSERT_EQ(13, serviceB._serviceA._value);
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactory_WhenFactoryRequiresOneServiceAsRef)
{
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 13; return serviceA; })
		.autoManaged();
	builder()
		.registerFactory([](ServiceA& serviceA) { return ServiceB(serviceA); });

	auto serviceB = container().resolve<ServiceB>();

	ASSERT_EQ(13, serviceB._serviceA._value);
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactory_WhenFactoryRequiresOneServiceAsPtr)
{
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 13; return serviceA; })
		.autoManaged();
	builder()
		.registerFactory([](ServiceA* serviceA) { return ServiceB(*serviceA); });

	auto serviceB = container().resolve<ServiceB>();

	ASSERT_EQ(13, serviceB._serviceA._value);
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactory_WhenFactoryRequiresOneServiceAsUniquePtr)
{
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 13; return serviceA; });
	builder()
		.registerFactory([](std::unique_ptr<ServiceA> serviceA) { return ServiceB(*serviceA); });

	auto serviceB = container().resolve<ServiceB>();

	ASSERT_EQ(13, serviceB._serviceA._value);
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactory_WhenFactoryRequiresOneServiceAsSharedPtr)
{
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 13; return serviceA; });
	builder()
		.registerFactory([](std::shared_ptr<ServiceA> serviceA) { return ServiceB(*serviceA); });

	auto serviceB = container().resolve<ServiceB>();

	ASSERT_EQ(13, serviceB._serviceA._value);
}