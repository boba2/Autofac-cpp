#include <stdafx.h>

#include "ContainerBaseTest.h"

using ServiceTypeWithDependencies = ContainerBaseTest;

namespace
{
	struct ServiceA { int _value = 13; };
	struct ServiceB { explicit ServiceB(ServiceA serviceA) : _serviceA(serviceA) {} const ServiceA _serviceA; };
	struct ServiceC { explicit ServiceC(ServiceA& serviceA) : _serviceA(serviceA) {} const ServiceA _serviceA; };
	struct ServiceD { explicit ServiceD(ServiceA* serviceA) : _serviceA(*serviceA) {} const ServiceA _serviceA; };
	struct ServiceE { explicit ServiceE(std::shared_ptr<ServiceA> serviceA) : _serviceA(*serviceA) {} const ServiceA _serviceA; };
	struct ServiceF { explicit ServiceF(std::unique_ptr<ServiceA> serviceA) : _serviceA(*serviceA) {} const ServiceA _serviceA; };
}

TEST_F(ServiceTypeWithDependencies, ShouldResolveServiceWithSingleObjectDependency)
{
	builder()
		.registerType<ServiceA>()
		.registerType<ServiceB>();

	auto serviceB = container().resolve<ServiceB>();

	ASSERT_EQ(13, serviceB._serviceA._value);
}

TEST_F(ServiceTypeWithDependencies, ShouldResolveServiceWithSingleRefDependency)
{
	builder()
		.registerType<ServiceA>()
			.autoManaged()
		.registerType<ServiceC>();

	auto serviceC = container().resolve<ServiceC>();

	ASSERT_EQ(13, serviceC._serviceA._value);
}

TEST_F(ServiceTypeWithDependencies, ShouldResolveServiceWithSinglePtrDependency)
{
	builder()
		.registerType<ServiceA>()
			.autoManaged()
		.registerType<ServiceD>();

	auto serviceD = container().resolve<ServiceD>();

	ASSERT_EQ(13, serviceD._serviceA._value);
}

TEST_F(ServiceTypeWithDependencies, ShouldResolveServiceWithSingleSharedPtrDependency)
{
	builder()
		.registerType<ServiceA>()
			.autoManaged()
		.registerType<ServiceE>();

	auto serviceE = container().resolve<ServiceE>();

	ASSERT_EQ(13, serviceE._serviceA._value);
}

TEST_F(ServiceTypeWithDependencies, ShouldResolveServiceWithSingleUniquePtrDependency)
{
	builder()
		.registerType<ServiceA>()
			.autoManaged()
		.registerType<ServiceF>();

	auto serviceF = container().resolve<ServiceF>();

	ASSERT_EQ(13, serviceF._serviceA._value);
}
