#include <gtest/gtest.h>
#include "../DITest/ContainerBuilder.h"
#include "DummyService.h"

struct ResolveRegisteredServiceInstanceTest : ::testing::Test
{
	ContainerBuilder *builder() const
	{
		return _container_builder.get();
	}

	Container *container()
	{
		return (_container ? _container : _container = builder()->build()).get();
	}

	std::unique_ptr<ContainerBuilder> _container_builder = std::make_unique<ContainerBuilder>();
	std::unique_ptr<Container> _container;
};

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByPointer_WhenServiceInstanceRegisteredThroughPointer)
{
	auto service = DummyService<>();

	builder()->registerInstance(&service);

	ASSERT_EQ(&service, container()->resolve<DummyService<> *>());
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByReference_WhenServiceInstanceRegisteredThroughPointer)
{
	auto service = DummyService<>();

	builder()->registerInstance(&service);

	ASSERT_EQ(&service, &container()->resolve<DummyService<> &>());
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByCopy_WhenServiceInstanceRegisteredThroughPointer)
{
	auto service = DummyService<>(13);

	builder()->registerInstance(&service);

	ASSERT_EQ(13, container()->resolve<DummyService<>>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceBySharedPtr_WhenServiceInstanceRegisteredThroughPointer)
{
	auto service = DummyService<>();

	builder()->registerInstance(&service);

	ASSERT_EQ(&service, container()->resolve<std::shared_ptr<DummyService<>>>().get());
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldThrowException_WhenResolvingServiceByUniquePtr_AndServiceInstanceRegisteredThroughPointer)
{
	auto service = DummyService<>();

	builder()->registerInstance(&service);

	ASSERT_THROW(container()->resolve<std::unique_ptr<DummyService<>>>(), Error::ServiceInstanceNotResolvableAsUniquePtr);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByPointer_WhenServiceInstanceRegisteredThroughCopy)
{
	auto service = DummyService<>(13);

	builder()->registerInstance(service);

	ASSERT_EQ(13, container()->resolve<DummyService<> *>()->_value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByReference_WhenServiceInstanceRegisteredThroughCopy)
{
	auto service = DummyService<>(13);

	builder()->registerInstance(service);

	ASSERT_EQ(13, container()->resolve<DummyService<> &>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByCopy_WhenServiceInstanceRegisteredThroughCopy)
{
	auto service = DummyService<>(13);

	builder()->registerInstance(service);

	ASSERT_EQ(13, container()->resolve<DummyService<>>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceBySharedPtr_WhenServiceInstanceRegisteredThroughCopy)
{
	auto service = DummyService<>(13);

	builder()->registerInstance(service);

	ASSERT_EQ(13, container()->resolve<std::shared_ptr<DummyService<>>>()->_value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldThrowException_WhenResolvingServiceByUniquePtr_AndServiceInstanceRegisteredThroughCopy)
{
	auto service = DummyService<>();

	builder()->registerInstance(service);

	ASSERT_THROW(container()->resolve<std::unique_ptr<DummyService<>>>(), Error::ServiceInstanceNotResolvableAsUniquePtr);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByPointer_WhenServiceInstanceRegisteredThroughMove)
{
	builder()->registerInstance(DummyService<>(13));

	ASSERT_EQ(13, container()->resolve<DummyService<> *>()->_value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByReference_WhenServiceInstanceRegisteredThroughMove)
{
	builder()->registerInstance(DummyService<>(13));

	ASSERT_EQ(13, container()->resolve<DummyService<> &>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByCopy_WhenServiceInstanceRegisteredThroughMove)
{
	builder()->registerInstance(DummyService<>(13));

	ASSERT_EQ(13, container()->resolve<DummyService<>>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceBySharedPtr_WhenServiceInstanceRegisteredThroughMove)
{
	builder()->registerInstance(DummyService<>(13));

	ASSERT_EQ(13, container()->resolve<std::shared_ptr<DummyService<>>>()->_value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldThrowException_WhenResolvingServiceByUniquePtr_AndServiceInstanceRegisteredThroughMove)
{
	builder()->registerInstance(DummyService<>());

	ASSERT_THROW(container()->resolve<std::unique_ptr<DummyService<>>>(), Error::ServiceInstanceNotResolvableAsUniquePtr);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByPointer_WhenServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<DummyService<>>();

	builder()->registerInstance(service);

	ASSERT_EQ(service.get(), container()->resolve<DummyService<> *>());
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByReference_WhenServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<DummyService<>>();

	builder()->registerInstance(service);

	ASSERT_EQ(service.get(), &container()->resolve<DummyService<> &>());
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByCopy_WhenServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<DummyService<>>(13);

	builder()->registerInstance(service);

	ASSERT_EQ(13, container()->resolve<DummyService<>>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceBySharedPtr_WhenServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<DummyService<>>();

	builder()->registerInstance(service);

	ASSERT_EQ(service.get(), container()->resolve<std::shared_ptr<DummyService<>>>().get());
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldThrowException_WhenResolvingServiceByUniquePtr_AndServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<DummyService<>>();

	builder()->registerInstance(service);

	ASSERT_THROW(container()->resolve<std::unique_ptr<DummyService<>>>(), Error::ServiceInstanceNotResolvableAsUniquePtr);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByPointer_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	builder()->registerInstance(std::make_unique<DummyService<>>(13));

	ASSERT_EQ(13, container()->resolve<DummyService<> *>()->_value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByReference_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	builder()->registerInstance(std::make_unique<DummyService<>>(13));

	ASSERT_EQ(13, container()->resolve<DummyService<> &>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByCopy_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	builder()->registerInstance(std::make_unique<DummyService<>>(13));

	ASSERT_EQ(13, container()->resolve<DummyService<>>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceBySharedPtr_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	builder()->registerInstance(std::make_unique<DummyService<>>(13));

	ASSERT_EQ(13, container()->resolve<std::shared_ptr<DummyService<>>>()->_value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldThrowException_WhenResolvingServiceByUniquePtr_AndServiceInstanceRegisteredThroughUniquePtr)
{
	builder()->registerInstance(std::make_unique<DummyService<>>(13));

	ASSERT_THROW(container()->resolve<std::unique_ptr<DummyService<>>>(), Error::ServiceInstanceNotResolvableAsUniquePtr);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveCorrectServiceByPointer_WhenServicesInstanceOfDifferentTypesRegistered)
{
	DummyService<1> service1;
	DummyService<2> service2;

	builder()->registerInstance(&service1);
	builder()->registerInstance(&service2);

	ASSERT_EQ(&service1, container()->resolve<DummyService<1> *>());
	ASSERT_EQ(&service2, container()->resolve<DummyService<2> *>());
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveCorrectServiceByReference_WhenServicesInstanceOfDifferentTypesRegistered)
{
	DummyService<1> service1;
	DummyService<2> service2;

	builder()->registerInstance(&service1);
	builder()->registerInstance(&service2);

	ASSERT_EQ(&service1, &container()->resolve<DummyService<1> &>());
	ASSERT_EQ(&service2, &container()->resolve<DummyService<2> &>());
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveCorrectServiceByCopy_WhenServicesInstanceOfDifferentTypesRegistered)
{
	DummyService<1> service1(13);
	DummyService<2> service2(14);

	builder()->registerInstance(&service1);
	builder()->registerInstance(&service2);

	ASSERT_EQ(13, container()->resolve<DummyService<1>>()._value);
	ASSERT_EQ(14, container()->resolve<DummyService<2>>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveCorrectServiceBySharedPtr_WhenServicesInstanceOfDifferentTypesRegistered)
{
	DummyService<1> service1;
	DummyService<2> service2;

	builder()->registerInstance(&service1);
	builder()->registerInstance(&service2);

	ASSERT_EQ(&service1, container()->resolve<std::shared_ptr<DummyService<1>>>().get());
	ASSERT_EQ(&service2, container()->resolve<std::shared_ptr<DummyService<2>>>().get());
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldThrowException_WhenResolvingServiceOfOtherTypeThanRegistered)
{
	DummyService<1> service1;

	builder()->registerInstance(&service1);

	ASSERT_THROW(container()->resolve<DummyService<2> *>(), Error::ServiceNotRegistered);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldNotMove_WhenRegisteringServiceInstanceAsLValue)
{
	DummyService<> service(13);

	builder()->registerInstance(service);

	ASSERT_EQ(13, service._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldTakeOwnershipOfService_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	auto service = std::make_unique<DummyService<>>();

	builder()->registerInstance(std::move(service));

	ASSERT_EQ(nullptr, service.get());
}

