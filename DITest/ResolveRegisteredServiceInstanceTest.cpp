#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>
#include "ServiceInstanceReferenceTypeConverter.h"
#include "Container.h"
#include "ContainerBuilder.h"
#include "DummyService.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(ResolveRegisteredServiceInstanceTest)
{
public:
	TEST_METHOD(ShouldResolveServiceByPointer_WhenServiceInstanceRegisteredThroughPointer)
	{
		auto service = DummyService<>();

		builder()->registerInstance(&service);

		Assert::IsTrue(container()->resolve<DummyService<> *>() == &service);
	}

	TEST_METHOD(ShouldResolveServiceByReference_WhenServiceInstanceRegisteredThroughPointer)
	{
		auto service = DummyService<>();

		builder()->registerInstance(&service);

		Assert::IsTrue(&container()->resolve<DummyService<> &>() == &service);
	}

	TEST_METHOD(ShouldResolveServiceByCopy_WhenServiceInstanceRegisteredThroughPointer)
	{
		auto service = DummyService<>(13);

		builder()->registerInstance(&service);

		Assert::AreEqual(13, container()->resolve<DummyService<>>()._value);
	}

	TEST_METHOD(ShouldResolveServiceBySharedPtr_WhenServiceInstanceRegisteredThroughPointer)
	{
		auto service = DummyService<>();

		builder()->registerInstance(&service);

		Assert::IsTrue(container()->resolve<std::shared_ptr<DummyService<>>>().get() == &service);
	}

	TEST_METHOD(ShouldThrowException_WhenResolvingServiceByUniquePtr_AndServiceInstanceRegisteredThroughPointer)
	{
		auto service = DummyService<>();

		builder()->registerInstance(&service);

		Assert::ExpectException<Error::ServiceInstanceNotResolvableAsUniquePtr>([this]
		{
			container()->resolve<std::unique_ptr<DummyService<>>>();
		});
	}

	TEST_METHOD(ShouldResolveServiceByPointer_WhenServiceInstanceRegisteredThroughCopy)
	{
		auto service = DummyService<>(13);

		builder()->registerInstance(service);

		Assert::AreEqual(13, container()->resolve<DummyService<> *>()->_value);
	}

	TEST_METHOD(ShouldResolveServiceByReference_WhenServiceInstanceRegisteredThroughCopy)
	{
		auto service = DummyService<>(13);

		builder()->registerInstance(service);

		Assert::AreEqual(13, container()->resolve<DummyService<> &>()._value);
	}

	TEST_METHOD(ShouldResolveServiceByCopy_WhenServiceInstanceRegisteredThroughCopy)
	{
		auto service = DummyService<>(13);

		builder()->registerInstance(service);

		Assert::AreEqual(13, container()->resolve<DummyService<>>()._value);
	}

	TEST_METHOD(ShouldResolveServiceBySharedPtr_WhenServiceInstanceRegisteredThroughCopy)
	{
		auto service = DummyService<>(13);

		builder()->registerInstance(service);

		Assert::AreEqual(13, container()->resolve<std::shared_ptr<DummyService<>>>()->_value);
	}

	TEST_METHOD(ShouldThrowException_WhenResolvingServiceByUniquePtr_AndServiceInstanceRegisteredThroughCopy)
	{
		auto service = DummyService<>();

		builder()->registerInstance(service);

		Assert::ExpectException<Error::ServiceInstanceNotResolvableAsUniquePtr>([this]
		{
			container()->resolve<std::unique_ptr<DummyService<>>>();
		});
	}

	TEST_METHOD(ShouldResolveServiceByPointer_WhenServiceInstanceRegisteredThroughMove)
	{
		builder()->registerInstance(DummyService<>(13));

		Assert::AreEqual(13, container()->resolve<DummyService<> *>()->_value);
	}

	TEST_METHOD(ShouldResolveServiceByReference_WhenServiceInstanceRegisteredThroughMove)
	{
		builder()->registerInstance(DummyService<>(13));

		Assert::AreEqual(13, container()->resolve<DummyService<> &>()._value);
	}

	TEST_METHOD(ShouldResolveServiceByCopy_WhenServiceInstanceRegisteredThroughMove)
	{
		builder()->registerInstance(DummyService<>(13));

		Assert::AreEqual(13, container()->resolve<DummyService<>>()._value);
	}

	TEST_METHOD(ShouldResolveServiceBySharedPtr_WhenServiceInstanceRegisteredThroughMove)
	{
		builder()->registerInstance(DummyService<>(13));

		Assert::AreEqual(13, container()->resolve<std::shared_ptr<DummyService<>>>()->_value);
	}

	TEST_METHOD(ShouldThrowException_WhenResolvingServiceByUniquePtr_AndServiceInstanceRegisteredThroughMove)
	{
		builder()->registerInstance(DummyService<>());

		Assert::ExpectException<Error::ServiceInstanceNotResolvableAsUniquePtr>([this]
		{
			container()->resolve<std::unique_ptr<DummyService<>>>();
		});
	}

	TEST_METHOD(ShouldResolveServiceByPointer_WhenServiceInstanceRegisteredThroughSharedPtr)
	{
		auto service = std::make_shared<DummyService<>>();

		builder()->registerInstance(service);

		Assert::IsTrue(container()->resolve<DummyService<> *>() == service.get());
	}

	TEST_METHOD(ShouldResolveServiceByReference_WhenServiceInstanceRegisteredThroughSharedPtr)
	{
		auto service = std::make_shared<DummyService<>>();

		builder()->registerInstance(service);

		Assert::IsTrue(&container()->resolve<DummyService<> &>() == service.get());
	}

	TEST_METHOD(ShouldResolveServiceByCopy_WhenServiceInstanceRegisteredThroughSharedPtr)
	{
		auto service = std::make_shared<DummyService<>>(13);

		builder()->registerInstance(service);

		Assert::AreEqual(13, container()->resolve<DummyService<>>()._value);
	}

	TEST_METHOD(ShouldResolveServiceBySharedPtr_WhenServiceInstanceRegisteredThroughSharedPtr)
	{
		auto service = std::make_shared<DummyService<>>();

		builder()->registerInstance(service);

		Assert::IsTrue(container()->resolve<std::shared_ptr<DummyService<>>>().get() == service.get());
	}

	TEST_METHOD(ShouldThrowException_WhenResolvingServiceByUniquePtr_AndServiceInstanceRegisteredThroughSharedPtr)
	{
		auto service = std::make_shared<DummyService<>>();

		builder()->registerInstance(service);

		Assert::ExpectException<Error::ServiceInstanceNotResolvableAsUniquePtr>([this]
		{
			container()->resolve<std::unique_ptr<DummyService<>>>();
		});
	}

	TEST_METHOD(ShouldResolveServiceByPointer_WhenServiceInstanceRegisteredThroughUniquePtr)
	{
		builder()->registerInstance(std::make_unique<DummyService<>>(13));

		Assert::AreEqual(13, container()->resolve<DummyService<> *>()->_value);
	}

	TEST_METHOD(ShouldResolveServiceByReference_WhenServiceInstanceRegisteredThroughUniquePtr)
	{
		builder()->registerInstance(std::make_unique<DummyService<>>(13));

		Assert::AreEqual(13, container()->resolve<DummyService<> &>()._value);
	}

	TEST_METHOD(ShouldResolveServiceByCopy_WhenServiceInstanceRegisteredThroughUniquePtr)
	{
		builder()->registerInstance(std::make_unique<DummyService<>>(13));

		Assert::AreEqual(13, container()->resolve<DummyService<>>()._value);
	}

	TEST_METHOD(ShouldResolveServiceBySharedPtr_WhenServiceInstanceRegisteredThroughUniquePtr)
	{
		builder()->registerInstance(std::make_unique<DummyService<>>(13));

		Assert::AreEqual(13, container()->resolve<std::shared_ptr<DummyService<>>>()->_value);
	}

	TEST_METHOD(ShouldThrowException_WhenResolvingServiceByUniquePtr_AndServiceInstanceRegisteredThroughUniquePtr)
	{
		builder()->registerInstance(std::make_unique<DummyService<>>(13));

		Assert::ExpectException<Error::ServiceInstanceNotResolvableAsUniquePtr>([this]
		{
			container()->resolve<std::unique_ptr<DummyService<>>>();
		});
	}

	TEST_METHOD(ShouldResolveCorrectServiceByPointer_WhenServicesInstanceOfDifferentTypesRegistered)
	{
		DummyService<1> service1;
		DummyService<2> service2;

		builder()->registerInstance(&service1);
		builder()->registerInstance(&service2);

		Assert::IsTrue(container()->resolve<DummyService<1> *>() == &service1);
		Assert::IsTrue(container()->resolve<DummyService<2> *>() == &service2);
	}

	TEST_METHOD(ShouldResolveCorrectServiceByReference_WhenServicesInstanceOfDifferentTypesRegistered)
	{
		DummyService<1> service1;
		DummyService<2> service2;

		builder()->registerInstance(&service1);
		builder()->registerInstance(&service2);

		Assert::IsTrue(&container()->resolve<DummyService<1> &>() == &service1);
		Assert::IsTrue(&container()->resolve<DummyService<2> &>() == &service2);
	}

	TEST_METHOD(ShouldResolveCorrectServiceByCopy_WhenServicesInstanceOfDifferentTypesRegistered)
	{
		DummyService<1> service1(13);
		DummyService<2> service2(14);

		builder()->registerInstance(&service1);
		builder()->registerInstance(&service2);

		Assert::AreEqual(13, container()->resolve<DummyService<1>>()._value);
		Assert::AreEqual(14, container()->resolve<DummyService<2>>()._value);
	}

	TEST_METHOD(ShouldResolveCorrectServiceBySharedPtr_WhenServicesInstanceOfDifferentTypesRegistered)
	{
		DummyService<1> service1;
		DummyService<2> service2;

		builder()->registerInstance(&service1);
		builder()->registerInstance(&service2);

		Assert::IsTrue(container()->resolve<std::shared_ptr<DummyService<1>>>().get() == &service1);
		Assert::IsTrue(container()->resolve<std::shared_ptr<DummyService<2>>>().get() == &service2);
	}

	TEST_METHOD(ShouldThrowException_WhenResolvingServiceOfOtherTypeThanRegistered)
	{
		DummyService<1> service1;

		builder()->registerInstance(&service1);

		Assert::ExpectException<Error::ServiceNotRegistered>([this]
		{
			container()->resolve<DummyService<2> *>();
		});
	}

	TEST_METHOD(ShouldNotMove_WhenRegisteringServiceInstanceAsLValue)
	{
		DummyService<> service(13);

		builder()->registerInstance(service);

		Assert::AreEqual(13, service._value);
	}

	TEST_METHOD(ShouldTakeOwnershipOfService_WhenServiceInstanceRegisteredThroughUniquePtr)
	{
		auto service = std::make_unique<DummyService<>>();

		builder()->registerInstance(std::move(service));

		Assert::IsNull(service.get());
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
