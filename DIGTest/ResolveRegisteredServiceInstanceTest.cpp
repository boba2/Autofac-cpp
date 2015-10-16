#include "ContainerBaseTest.h"
#include "DummyService.h"

TEST_F(ContainerBaseTest, ShouldResolveServiceByPointer_WhenServiceInstanceRegisteredThroughPointer)
{
	auto service = DummyService<>();

	builder().registerInstance(&service);

	ASSERT_EQ(&service, container().resolve<DummyService<> *>());
}

TEST_F(ContainerBaseTest, ShouldResolveServiceByReference_WhenServiceInstanceRegisteredThroughPointer)
{
	auto service = DummyService<>();

	builder().registerInstance(&service);

	ASSERT_EQ(&service, &container().resolve<DummyService<> &>());
}

TEST_F(ContainerBaseTest, ShouldResolveServiceByCopy_WhenServiceInstanceRegisteredThroughPointer)
{
	auto service = DummyService<>(13);

	builder().registerInstance(&service);

	ASSERT_EQ(13, container().resolve<DummyService<>>()._value);
}

TEST_F(ContainerBaseTest, ShouldResolveServiceBySharedPtr_WhenServiceInstanceRegisteredThroughPointer)
{
	auto service = DummyService<>();

	builder().registerInstance(&service);

	ASSERT_EQ(&service, container().resolve<std::shared_ptr<DummyService<>>>().get());
}

TEST_F(ContainerBaseTest, ShouldThrowException_WhenResolvingServiceByUniquePtr_AndServiceInstanceRegisteredThroughPointer)
{
	auto service = DummyService<>();

	builder().registerInstance(&service);

	ASSERT_THROW(container().resolve<std::unique_ptr<DummyService<>>>(), Error::ServiceInstanceNotResolvableAsUniquePtr);
}

TEST_F(ContainerBaseTest, ShouldResolveServiceByPointer_WhenServiceInstanceRegisteredThroughCopy)
{
	auto service = DummyService<>(13);

	builder().registerInstance(service);

	ASSERT_EQ(13, container().resolve<DummyService<> *>()->_value);
}

TEST_F(ContainerBaseTest, ShouldResolveServiceByReference_WhenServiceInstanceRegisteredThroughCopy)
{
	auto service = DummyService<>(13);

	builder().registerInstance(service);

	ASSERT_EQ(13, container().resolve<DummyService<> &>()._value);
}

TEST_F(ContainerBaseTest, ShouldResolveServiceByCopy_WhenServiceInstanceRegisteredThroughCopy)
{
	auto service = DummyService<>(13);

	builder().registerInstance(service);

	ASSERT_EQ(13, container().resolve<DummyService<>>()._value);
}

TEST_F(ContainerBaseTest, ShouldResolveServiceBySharedPtr_WhenServiceInstanceRegisteredThroughCopy)
{
	auto service = DummyService<>(13);

	builder().registerInstance(service);

	ASSERT_EQ(13, container().resolve<std::shared_ptr<DummyService<>>>()->_value);
}

TEST_F(ContainerBaseTest, ShouldThrowException_WhenResolvingServiceByUniquePtr_AndServiceInstanceRegisteredThroughCopy)
{
	auto service = DummyService<>();

	builder().registerInstance(service);

	ASSERT_THROW(container().resolve<std::unique_ptr<DummyService<>>>(), Error::ServiceInstanceNotResolvableAsUniquePtr);
}

TEST_F(ContainerBaseTest, ShouldResolveServiceByPointer_WhenServiceInstanceRegisteredThroughMove)
{
	builder().registerInstance(DummyService<>(13));

	ASSERT_EQ(13, container().resolve<DummyService<> *>()->_value);
}

TEST_F(ContainerBaseTest, ShouldResolveServiceByReference_WhenServiceInstanceRegisteredThroughMove)
{
	builder().registerInstance(DummyService<>(13));

	ASSERT_EQ(13, container().resolve<DummyService<> &>()._value);
}

TEST_F(ContainerBaseTest, ShouldResolveServiceByCopy_WhenServiceInstanceRegisteredThroughMove)
{
	builder().registerInstance(DummyService<>(13));

	ASSERT_EQ(13, container().resolve<DummyService<>>()._value);
}

TEST_F(ContainerBaseTest, ShouldResolveServiceBySharedPtr_WhenServiceInstanceRegisteredThroughMove)
{
	builder().registerInstance(DummyService<>(13));

	ASSERT_EQ(13, container().resolve<std::shared_ptr<DummyService<>>>()->_value);
}

TEST_F(ContainerBaseTest, ShouldThrowException_WhenResolvingServiceByUniquePtr_AndServiceInstanceRegisteredThroughMove)
{
	builder().registerInstance(DummyService<>());

	ASSERT_THROW(container().resolve<std::unique_ptr<DummyService<>>>(), Error::ServiceInstanceNotResolvableAsUniquePtr);
}

TEST_F(ContainerBaseTest, ShouldResolveServiceByPointer_WhenServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<DummyService<>>();

	builder().registerInstance(service);

	ASSERT_EQ(service.get(), container().resolve<DummyService<> *>());
}

TEST_F(ContainerBaseTest, ShouldResolveServiceByReference_WhenServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<DummyService<>>();

	builder().registerInstance(service);

	ASSERT_EQ(service.get(), &container().resolve<DummyService<> &>());
}

TEST_F(ContainerBaseTest, ShouldResolveServiceByCopy_WhenServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<DummyService<>>(13);

	builder().registerInstance(service);

	ASSERT_EQ(13, container().resolve<DummyService<>>()._value);
}

TEST_F(ContainerBaseTest, ShouldResolveServiceBySharedPtr_WhenServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<DummyService<>>();

	builder().registerInstance(service);

	ASSERT_EQ(service.get(), container().resolve<std::shared_ptr<DummyService<>>>().get());
}

TEST_F(ContainerBaseTest, ShouldThrowException_WhenResolvingServiceByUniquePtr_AndServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<DummyService<>>();

	builder().registerInstance(service);

	ASSERT_THROW(container().resolve<std::unique_ptr<DummyService<>>>(), Error::ServiceInstanceNotResolvableAsUniquePtr);
}

TEST_F(ContainerBaseTest, ShouldResolveServiceByPointer_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	builder().registerInstance(std::make_unique<DummyService<>>(13));

	ASSERT_EQ(13, container().resolve<DummyService<> *>()->_value);
}

TEST_F(ContainerBaseTest, ShouldResolveServiceByReference_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	builder().registerInstance(std::make_unique<DummyService<>>(13));

	ASSERT_EQ(13, container().resolve<DummyService<> &>()._value);
}

TEST_F(ContainerBaseTest, ShouldResolveServiceByCopy_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	builder().registerInstance(std::make_unique<DummyService<>>(13));

	ASSERT_EQ(13, container().resolve<DummyService<>>()._value);
}

TEST_F(ContainerBaseTest, ShouldResolveServiceBySharedPtr_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	builder().registerInstance(std::make_unique<DummyService<>>(13));

	ASSERT_EQ(13, container().resolve<std::shared_ptr<DummyService<>>>()->_value);
}

TEST_F(ContainerBaseTest, ShouldThrowException_WhenResolvingServiceByUniquePtr_AndServiceInstanceRegisteredThroughUniquePtr)
{
	builder().registerInstance(std::make_unique<DummyService<>>(13));

	ASSERT_THROW(container().resolve<std::unique_ptr<DummyService<>>>(), Error::ServiceInstanceNotResolvableAsUniquePtr);
}

TEST_F(ContainerBaseTest, ShouldResolveCorrectServiceByPointer_WhenServicesInstanceOfDifferentTypesRegistered)
{
	DummyService<1> service1;
	DummyService<2> service2;

	builder().registerInstance(&service1);
	builder().registerInstance(&service2);

	ASSERT_EQ(&service1, container().resolve<DummyService<1> *>());
	ASSERT_EQ(&service2, container().resolve<DummyService<2> *>());
}

TEST_F(ContainerBaseTest, ShouldResolveCorrectServiceByReference_WhenServicesInstanceOfDifferentTypesRegistered)
{
	DummyService<1> service1;
	DummyService<2> service2;

	builder().registerInstance(&service1);
	builder().registerInstance(&service2);

	ASSERT_EQ(&service1, &container().resolve<DummyService<1> &>());
	ASSERT_EQ(&service2, &container().resolve<DummyService<2> &>());
}

TEST_F(ContainerBaseTest, ShouldResolveCorrectServiceByCopy_WhenServicesInstanceOfDifferentTypesRegistered)
{
	DummyService<1> service1(13);
	DummyService<2> service2(14);

	builder().registerInstance(&service1);
	builder().registerInstance(&service2);

	ASSERT_EQ(13, container().resolve<DummyService<1>>()._value);
	ASSERT_EQ(14, container().resolve<DummyService<2>>()._value);
}

TEST_F(ContainerBaseTest, ShouldResolveCorrectServiceBySharedPtr_WhenServicesInstanceOfDifferentTypesRegistered)
{
	DummyService<1> service1;
	DummyService<2> service2;

	builder().registerInstance(&service1);
	builder().registerInstance(&service2);

	ASSERT_EQ(&service1, container().resolve<std::shared_ptr<DummyService<1>>>().get());
	ASSERT_EQ(&service2, container().resolve<std::shared_ptr<DummyService<2>>>().get());
}

TEST_F(ContainerBaseTest, ShouldThrowException_WhenResolvingServiceOfOtherTypeThanRegistered)
{
	DummyService<1> service1;

	builder().registerInstance(&service1);

	ASSERT_THROW(container().resolve<DummyService<2> *>(), Error::ServiceNotRegistered);
}

TEST_F(ContainerBaseTest, ShouldNotMove_WhenRegisteringServiceInstanceAsLValue)
{
	DummyService<> service(13);

	builder().registerInstance(service);

	ASSERT_EQ(13, service._value);
}

TEST_F(ContainerBaseTest, ShouldTakeOwnershipOfService_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	auto service = std::make_unique<DummyService<>>();

	builder().registerInstance(std::move(service));

	ASSERT_EQ(nullptr, service.get());
}

