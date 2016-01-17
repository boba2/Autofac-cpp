#include <stdafx.h>

#include "ContainerBaseTest.h"

namespace
{
	struct ServiceA { int _value; };
	struct ServiceB { explicit ServiceB(ServiceA serviceA) : _serviceA(serviceA) {} ServiceA _serviceA; };
}

using StandardServiceInstanceTest = ContainerBaseTest;

TEST_F(StandardServiceInstanceTest, ShouldResolveContainerAsObject)
{
	auto service = container().resolve<DI::Container>();

	ASSERT_TRUE(isOfType<DI::Container>(service));
}

TEST_F(StandardServiceInstanceTest, ShouldResolveContainerAsPtr)
{
	auto service = container().resolve<DI::Container*>();

	ASSERT_TRUE(isOfType<DI::Container>(service));
}

TEST_F(StandardServiceInstanceTest, ShouldResolveContainerAsRef)
{
	auto service = container().resolve<DI::Container&>();

	ASSERT_TRUE(isOfType<DI::Container>(service));
}

TEST_F(StandardServiceInstanceTest, ShouldResolveContainerAsSharedPtr)
{
	auto service = container().resolve<std::shared_ptr<DI::Container>>();

	ASSERT_TRUE(isOfType<DI::Container>(service.get()));
}

TEST_F(StandardServiceInstanceTest, ShouldThrowException_WhenResolvingContainerAsUniquePtr)
{
	ASSERT_THROW(container().resolve<std::unique_ptr<DI::Container>>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(StandardServiceInstanceTest, ShouldResolveContainerAsSingleInstance)
{
	auto service1 = container().resolve<DI::Container*>();
	auto service2 = container().resolve<DI::Container*>();

	ASSERT_EQ(service1, service2);
}

TEST_F(StandardServiceInstanceTest, ShouldResolveSameSingleServiceInstancefromDifferentContainerCopies)
{
	builder()
		.registerType<ServiceA>()
		.singleInstance();

	auto container_copy = container().resolve<DI::Container>();

	auto service1 = container().resolve<ServiceA *>();
	auto service2 = container_copy.resolve<ServiceA *>();

	ASSERT_EQ(service1, service2);
}

TEST_F(StandardServiceInstanceTest, ShouldResolveSameRegisteredServiceInstanceFromDifferentContainerCopies)
{
	builder().registerInstance(ServiceA());
	auto container_copy = container().resolve<DI::Container>();

	auto service1 = container().resolve<ServiceA *>();
	auto service2 = container_copy.resolve<ServiceA *>();

	ASSERT_EQ(service1, service2);
}

TEST_F(StandardServiceInstanceTest, ShouldPassContainerToFactory_WhenFactoryRequiresContainer_AndFactoryAsLambda)
{
	builder()
		.registerFactory([] { auto service = ServiceA(); service._value = 13; return service; })
		.registerFactory([](DI::Container& container) { return ServiceB(container.resolve<ServiceA>()); });

	auto service = container().resolve<ServiceB>();

	ASSERT_EQ(13, service._serviceA._value);
}

TEST_F(StandardServiceInstanceTest, ShouldPassContainerToFactory_WhenFactoryRequiresContainer_AndFactoryAsFunction)
{
	builder()
		.registerFactory([] { auto service = ServiceA(); service._value = 13; return service; })
		.registerFactory(static_cast<std::function<ServiceB(DI::Container&)>>([](DI::Container& container) { return ServiceB(container.resolve<ServiceA>()); }));

	auto service = container().resolve<ServiceB>();

	ASSERT_EQ(13, service._serviceA._value);
}

TEST_F(StandardServiceInstanceTest, ShouldPassContainerToFactoryAsObject)
{
	builder()
		.registerFactory([] { auto service = ServiceA(); service._value = 13; return service; })
		.registerFactory([](DI::Container container) { return ServiceB(container.resolve<ServiceA>()); });

	auto service = container().resolve<ServiceB>();

	ASSERT_EQ(13, service._serviceA._value);
}

TEST_F(StandardServiceInstanceTest, ShouldPassContainerToFactoryAsRef)
{
	builder()
		.registerFactory([] { auto service = ServiceA(); service._value = 13; return service; })
		.registerFactory([](DI::Container& container) { return ServiceB(container.resolve<ServiceA>()); });

	auto service = container().resolve<ServiceB>();

	ASSERT_EQ(13, service._serviceA._value);
}

TEST_F(StandardServiceInstanceTest, ShouldPassContainerToFactoryAsPtr)
{
	builder()
		.registerFactory([] { auto service = ServiceA(); service._value = 13; return service; })
		.registerFactory([](DI::Container* container) { return ServiceB(container->resolve<ServiceA>()); });

	auto service = container().resolve<ServiceB>();

	ASSERT_EQ(13, service._serviceA._value);
}

TEST_F(StandardServiceInstanceTest, ShouldPassContainerToFactoryAsSharedPtr)
{
	builder()
		.registerFactory([] { auto service = ServiceA(); service._value = 13; return service; })
		.registerFactory([](std::shared_ptr<DI::Container> container) { return ServiceB(container->resolve<ServiceA>()); });

	auto service = container().resolve<ServiceB>();

	ASSERT_EQ(13, service._serviceA._value);
}

TEST_F(StandardServiceInstanceTest, ShouldThrowException_WhenPassingContainerToFactoryAsUniquePtr)
{
	builder()
		.registerFactory([] { auto service = ServiceA(); service._value = 13; return service; })
		.registerFactory([](std::unique_ptr<DI::Container> container) { return ServiceB(container->resolve<ServiceA>()); });

	ASSERT_THROW(container().resolve<ServiceB>(), DI::Error::ServiceNotResolvableAs);
}