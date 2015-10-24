#include "ContainerBaseTest.h"

using ResolveServiceTypeWithDependencies = ContainerBaseTest;

namespace
{
	struct ServiceA { int _value = 13; };
	struct ServiceB { explicit ServiceB(ServiceA serviceA) : _serviceA(serviceA) {} const ServiceA _serviceA; };
}

TEST_F(ResolveServiceTypeWithDependencies, ShouldResolveServiceWithSingleSimpleDependency)
{
	builder().registerType<ServiceA>();
	builder().registerType<ServiceB>();

	auto serviceB = container().resolve<ServiceB>();

	ASSERT_EQ(13, serviceB._serviceA._value);
}