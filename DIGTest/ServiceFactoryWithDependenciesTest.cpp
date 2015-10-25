#include <stdafx.h>

#include "ContainerBaseTest.h"

using ServiceFactoryWithDependenciesTest = ContainerBaseTest;

namespace
{
	struct ServiceA { int _value; };
	struct ServiceB { explicit ServiceB(ServiceA serviceA) : _serviceA(serviceA) {} ServiceA _serviceA; };
	struct ServiceC { explicit ServiceC(ServiceA serviceA, ServiceB serviceB) : _serviceA(serviceA), _serviceB(serviceB) {} ServiceA _serviceA; ServiceB _serviceB; };
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactoryLambda_WhenFactoryRequiresOneServiceAsObject)
{
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 11; return serviceA; })
		.registerFactory([](ServiceA serviceA) { return ServiceB(serviceA); });

	auto serviceB = container().resolve<ServiceB>();

	ASSERT_EQ(11, serviceB._serviceA._value);
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactoryLambda_WhenFactoryRequiresOneServiceAsRef)
{
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 12; return serviceA; })
			.autoManaged()
		.registerFactory([](ServiceA& serviceA) { return ServiceB(serviceA); });

	auto serviceB = container().resolve<ServiceB>();

	ASSERT_EQ(12, serviceB._serviceA._value);
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactoryLambda_WhenFactoryRequiresOneServiceAsPtr)
{
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 13; return serviceA; })
			.autoManaged()
		.registerFactory([](ServiceA* serviceA) { return ServiceB(*serviceA); });

	auto serviceB = container().resolve<ServiceB>();

	ASSERT_EQ(13, serviceB._serviceA._value);
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactoryLambda_WhenFactoryRequiresOneServiceAsSharedPtr)
{
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 14; return serviceA; })
		.registerFactory([](std::shared_ptr<ServiceA> serviceA) { return ServiceB(*serviceA); });

	auto serviceB = container().resolve<ServiceB>();

	ASSERT_EQ(14, serviceB._serviceA._value);
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactoryLambda_WhenFactoryRequiresOneServiceAsUniquePtr)
{
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 15; return serviceA; })
		.registerFactory([](std::unique_ptr<ServiceA> serviceA) { return ServiceB(*serviceA); });

	auto serviceB = container().resolve<ServiceB>();

	ASSERT_EQ(15, serviceB._serviceA._value);
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactoryFunction_WhenFactoryRequiresOneServiceAsObject)
{
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 16; return serviceA; })
		.registerFactory(static_cast<std::function<ServiceB(ServiceA)>>([](ServiceA serviceA) { return ServiceB(serviceA); }));

	auto serviceB = container().resolve<ServiceB>();

	ASSERT_EQ(16, serviceB._serviceA._value);
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactoryFunction_WhenFactoryRequiresOneServiceAsRef)
{
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 17; return serviceA; })
			.autoManaged()
		.registerFactory(static_cast<std::function<ServiceB(ServiceA&)>>([](ServiceA& serviceA) { return ServiceB(serviceA); }));

	auto serviceB = container().resolve<ServiceB>();

	ASSERT_EQ(17, serviceB._serviceA._value);
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactoryFunction_WhenFactoryRequiresOneServiceAsPtr)
{
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 18; return serviceA; })
			.autoManaged()
		.registerFactory(static_cast<std::function<ServiceB(ServiceA*)>>([](ServiceA* serviceA) { return ServiceB(*serviceA); }));

	auto serviceB = container().resolve<ServiceB>();

	ASSERT_EQ(18, serviceB._serviceA._value);
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactoryFunction_WhenFactoryRequiresOneServiceAsSharedPtr)
{
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 19; return serviceA; })
		.registerFactory(static_cast<std::function<ServiceB(std::shared_ptr<ServiceA>)>>([](std::shared_ptr<ServiceA> serviceA) { return ServiceB(*serviceA); }));

	auto serviceB = container().resolve<ServiceB>();

	ASSERT_EQ(19, serviceB._serviceA._value);
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactoryFunction_WhenFactoryRequiresOneServiceAsUniquePtr)
{
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 20; return serviceA; })
		.registerFactory(static_cast<std::function<ServiceB(std::unique_ptr<ServiceA>)>>([](std::unique_ptr<ServiceA> serviceA) { return ServiceB(*serviceA); }));

	auto serviceB = container().resolve<ServiceB>();

	ASSERT_EQ(20, serviceB._serviceA._value);
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactoryLambda_WhenFactoryRequiresMultipleServicesAsObjects)
{
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 11; return serviceA; })
		.registerType<ServiceB>()
		.registerFactory([](ServiceA serviceA, ServiceB serviceB) { return ServiceC(serviceA, serviceB); });

	auto serviceC = container().resolve<ServiceC>();

	ASSERT_EQ(11, serviceC._serviceA._value);
	ASSERT_EQ(11, serviceC._serviceB._serviceA._value);
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactoryLambda_WhenFactoryRequiresMultipleServicesAsDifferentTypes_1)
{
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 11; return serviceA; })
			.autoManaged()
		.registerType<ServiceB>()
			.autoManaged()
		.registerFactory([](ServiceA* serviceA, ServiceB& serviceB) { return ServiceC(*serviceA, serviceB); });

	auto serviceC = container().resolve<ServiceC>();

	ASSERT_EQ(11, serviceC._serviceA._value);
	ASSERT_EQ(11, serviceC._serviceB._serviceA._value);
}

TEST_F(ServiceFactoryWithDependenciesTest, ShouldResolveServiceFromFactoryLambda_WhenFactoryRequiresMultipleServicesAsDifferentTypes_2)
{
	builder()
		.registerFactory([] { auto serviceA = ServiceA(); serviceA._value = 11; return serviceA; })
		.registerType<ServiceB>()
		.registerFactory([](std::shared_ptr<ServiceA> serviceA, std::unique_ptr<ServiceB> serviceB) { return ServiceC(*serviceA, *serviceB); });

	auto serviceC = container().resolve<ServiceC>();

	ASSERT_EQ(11, serviceC._serviceA._value);
	ASSERT_EQ(11, serviceC._serviceB._serviceA._value);
}