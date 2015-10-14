#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>
#include "ServiceInstanceReferenceTypeConverter.h"
#include "Container.h"
#include "ContainerBuilder.h"
#include "DummyService.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(BaseContainerTest)
{
public:
	TEST_METHOD(ShouldResolveServiceByType_WhenServiceRegisteredThroughPointer)
	{
		DummyService<> service;

		builder()->registerInstance(&service);

		Assert::IsTrue(container()->resolve<DummyService<> *>() == &service);
	}

	TEST_METHOD(ShouldResolveServiceOfCorrectType_WhenServicesOfDifferentTypesRegisteredThroughPointers)
	{
		DummyService<1> service1;
		DummyService<2> service2;

		builder()->registerInstance(&service1);
		builder()->registerInstance(&service2);

		Assert::IsTrue(container()->resolve<DummyService<1> *>() == &service1);
		Assert::IsTrue(container()->resolve<DummyService<2> *>() == &service2);
	}

	TEST_METHOD(ShouldThrowException_WhenResolvingServiceOfUnregisteredType)
	{
		DummyService<1> service1;

		builder()->registerInstance(&service1);

		Assert::ExpectException<Error::ServiceNotRegistered>([this]
		{
			container()->resolve<DummyService<2> *>();
		});
	}

	TEST_METHOD(ShouldResolveCopyOfService_WhenServiceInstanceRegistered)
	{
		builder()->registerInstance(DummyService<>(13));

		Assert::AreEqual(13, container()->resolve<DummyService<> *>()->_value);
	}

	TEST_METHOD(ShouldResolveCopyOfServiceOfCorrectType_WhenServiceInstancesOfDifferentTypesRegistered)
	{
		builder()->registerInstance(DummyService<1>(13));
		builder()->registerInstance(DummyService<2>(14));

		Assert::AreEqual(13, container()->resolve<DummyService<1> *>()->_value);
		Assert::AreEqual(14, container()->resolve<DummyService<2> *>()->_value);
	}

	TEST_METHOD(ShouldResolveCopyOfService_WhenServiceInstanceRegisteredByCopy)
	{
		DummyService<> service(13);

		builder()->registerInstance(service);

		Assert::AreEqual(13, container()->resolve<DummyService<> *>()->_value);
	}

	TEST_METHOD(ShouldNotMove_WhenRegisteringLValueServiceInstance)
	{
		DummyService<> service(13);

		builder()->registerInstance(service);

		Assert::AreEqual(13, service._value);
	}

	TEST_METHOD(ShouldResolveServiceByType_WhenServiceRegisteredThroughSharedPtr)
	{
		auto service = std::make_shared<DummyService<>>();

		builder()->registerInstance(service);

		Assert::IsTrue(container()->resolve<DummyService<> *>() == service.get());
	}

	TEST_METHOD(ShouldResolveServiceOfCorrectType_WhenServiceInstancesOfDifferentTypesRegisteredThroughSharedPtr)
	{
		auto service1 = std::make_shared<DummyService<1>>();
		auto service2 = std::make_shared<DummyService<2>>();

		builder()->registerInstance(service1);
		builder()->registerInstance(service2);

		Assert::IsTrue(container()->resolve<DummyService<1> *>() == service1.get());
		Assert::IsTrue(container()->resolve<DummyService<2> *>() == service2.get());
	}

	TEST_METHOD(ShouldHoldServiceInstance_WhenRegisteredReferenceDestroyed)
	{
		builder()->registerInstance(std::make_shared<DummyService<>>(15));

		Assert::AreEqual(15, container()->resolve<DummyService<> *>()->_value);
	}

	TEST_METHOD(ShouldAllowRegisteringServiceThroughUniquePtr)
	{
		builder()->registerInstance(std::make_unique<DummyService<>>(13));

		Assert::AreEqual(13, container()->resolve<DummyService<> *>()->_value);
	}

	TEST_METHOD(ShouldTakeOwnershipOfServiceRegisteredThroughUniquePtr)
	{
		auto service = std::make_unique<DummyService<>>();

		builder()->registerInstance(std::move(service));

		Assert::IsNull(service.get());
	}

	TEST_METHOD(ShouldResolveServiceInstanceByReference)
	{
		auto service = std::make_shared<DummyService<>>();

		builder()->registerInstance(service);

		Assert::IsTrue(&container()->resolve<DummyService<> &>() == service.get());
	}

	TEST_METHOD(ShouldResolveServiceInstanceBySharedPtr)
	{
		auto service = std::make_shared<DummyService<>>();

		builder()->registerInstance(service);

		Assert::IsTrue(container()->resolve<std::shared_ptr<DummyService<>>>() == service);
	}

	TEST_METHOD(ShouldThrowException_WhenResolvingServiceInstanceByUniquePtr)
	{
		auto service = std::make_shared<DummyService<>>();

		builder()->registerInstance(service);

		Assert::ExpectException<Error::ServiceInstanceNotResolvableAsUniquePtr>([this]
		{
			container()->resolve<std::unique_ptr<DummyService<>>>();
		});
	}

	TEST_METHOD(ShouldResolveServiceInstanceAsCopy)
	{
		auto service = std::make_shared<DummyService<>>(13);

		builder()->registerInstance(service);

		auto service2 = container()->resolve<DummyService<>>();

		Assert::AreEqual(13, service2._value);
	}

private:
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
