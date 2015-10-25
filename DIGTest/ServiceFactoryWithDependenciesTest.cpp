#include <stdafx.h>

#include "ContainerBaseTest.h"

using ServiceFactoryWithDependenciesTest = ContainerBaseTest;

namespace
{
	struct ServiceA { int _value; };
	struct ServiceB { explicit ServiceB(ServiceA serviceA) : _serviceA(serviceA) {} ServiceA _serviceA; };
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactoryLambda_WhenFactoryRequiresOneServiceAsObject)
{
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 11; return serviceA; });
	builder()
		.registerFactory([](ServiceA serviceA) { return ServiceB(serviceA); });

	auto serviceB = container().resolve<ServiceB>();

	ASSERT_EQ(11, serviceB._serviceA._value);
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactoryLambda_WhenFactoryRequiresOneServiceAsRef)
{
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 12; return serviceA; })
		.autoManaged();
	builder()
		.registerFactory([](ServiceA& serviceA) { return ServiceB(serviceA); });

	auto serviceB = container().resolve<ServiceB>();

	ASSERT_EQ(12, serviceB._serviceA._value);
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactoryLambda_WhenFactoryRequiresOneServiceAsPtr)
{
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 13; return serviceA; })
		.autoManaged();
	builder()
		.registerFactory([](ServiceA* serviceA) { return ServiceB(*serviceA); });

	auto serviceB = container().resolve<ServiceB>();

	ASSERT_EQ(13, serviceB._serviceA._value);
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactoryLambda_WhenFactoryRequiresOneServiceAsSharedPtr)
{
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 14; return serviceA; });
	builder()
		.registerFactory([](std::shared_ptr<ServiceA> serviceA) { return ServiceB(*serviceA); });

	auto serviceB = container().resolve<ServiceB>();

	ASSERT_EQ(14, serviceB._serviceA._value);
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactoryLambda_WhenFactoryRequiresOneServiceAsUniquePtr)
{
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 15; return serviceA; });
	builder()
		.registerFactory([](std::unique_ptr<ServiceA> serviceA) { return ServiceB(*serviceA); });

	auto serviceB = container().resolve<ServiceB>();

	ASSERT_EQ(15, serviceB._serviceA._value);
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactoryFunction_WhenFactoryRequiresOneServiceAsObject)
{
	std::function<ServiceB(ServiceA)> factory = [](ServiceA serviceA) { return ServiceB(serviceA); };
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 16; return serviceA; });
	builder()
		.registerFactory(factory);

	auto serviceB = container().resolve<ServiceB>();

	ASSERT_EQ(16, serviceB._serviceA._value);
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactoryFunction_WhenFactoryRequiresOneServiceAsRef)
{
	std::function<ServiceB(ServiceA&)> factory = [](ServiceA& serviceA) { return ServiceB(serviceA); };
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 17; return serviceA; })
		.autoManaged();
	builder()
		.registerFactory(factory);

	auto serviceB = container().resolve<ServiceB>();

	ASSERT_EQ(17, serviceB._serviceA._value);
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactoryFunction_WhenFactoryRequiresOneServiceAsPtr)
{
	std::function<ServiceB(ServiceA*)> factory = [](ServiceA* serviceA) { return ServiceB(*serviceA); };
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 18; return serviceA; })
		.autoManaged();
	builder()
		.registerFactory(factory);

	auto serviceB = container().resolve<ServiceB>();

	ASSERT_EQ(18, serviceB._serviceA._value);
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactoryFunction_WhenFactoryRequiresOneServiceAsSharedPtr)
{
	std::function<ServiceB(std::shared_ptr<ServiceA>)> factory = [](std::shared_ptr<ServiceA> serviceA) { return ServiceB(*serviceA); };
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 19; return serviceA; });
	builder()
		.registerFactory(factory);

	auto serviceB = container().resolve<ServiceB>();

	ASSERT_EQ(19, serviceB._serviceA._value);
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactoryFunction_WhenFactoryRequiresOneServiceAsUniquePtr)
{
	std::function<ServiceB(std::unique_ptr<ServiceA>)> factory = [](std::unique_ptr<ServiceA> serviceA) { return ServiceB(*serviceA); };
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 20; return serviceA; });
	builder()
		.registerFactory(factory);

	auto serviceB = container().resolve<ServiceB>();

	ASSERT_EQ(20, serviceB._serviceA._value);
}