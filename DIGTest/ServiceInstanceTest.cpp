#include <stdafx.h>

#include "ContainerBaseTest.h"
#include "../DI/Error/ServiceNotRegistered.h"

namespace
{
	class DummyService
	{
	public:
		int _value;
		explicit DummyService(const int value = 0) : _value(value) {}
		DummyService(const DummyService &other) = default;
		DummyService(DummyService &&other) = default;
		DummyService &operator=(const DummyService &other) = default;
		DummyService &operator=(DummyService &&other) = default;
	};

	struct DummyService1
	{
		int _value;
		explicit DummyService1(const int value = 0) : _value(value) {}
	};

	struct DummyService2
	{
		int _value;
		explicit DummyService2(const int value = 0) : _value(value) {}
	};
}

using ServiceInstanceTest = ContainerBaseTest;

TEST_F(ServiceInstanceTest, ShouldResolveServiceAsPointer_WhenServiceInstanceRegisteredThroughPointer)
{
	auto service = DummyService();

	builder().registerInstance(&service);

	ASSERT_EQ(&service, container().resolve<DummyService *>());
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceAsReference_WhenServiceInstanceRegisteredThroughPointer)
{
	auto service = DummyService();

	builder().registerInstance(&service);

	ASSERT_EQ(&service, &container().resolve<DummyService &>());
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceAsCopy_WhenServiceInstanceRegisteredThroughPointer)
{
	auto service = DummyService(13);

	builder().registerInstance(&service);

	ASSERT_EQ(13, container().resolve<DummyService>()._value);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceAsSharedPtr_WhenServiceInstanceRegisteredThroughPointer)
{
	auto service = DummyService();

	builder().registerInstance(&service);

	ASSERT_EQ(&service, container().resolve<std::shared_ptr<DummyService>>().get());
}

TEST_F(ServiceInstanceTest, ShouldThrowException_WhenResolvingServiceAsUniquePtr_AndServiceInstanceRegisteredThroughPointer)
{
	auto service = DummyService();

	builder().registerInstance(&service);

	ASSERT_THROW(container().resolve<std::unique_ptr<DummyService>>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceAsPointer_WhenServiceInstanceRegisteredThroughCopy)
{
	auto service = DummyService(13);

	builder().registerInstance(service);

	ASSERT_EQ(13, container().resolve<DummyService *>()->_value);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceAsReference_WhenServiceInstanceRegisteredThroughCopy)
{
	auto service = DummyService(13);

	builder().registerInstance(service);

	ASSERT_EQ(13, container().resolve<DummyService &>()._value);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceAsCopy_WhenServiceInstanceRegisteredThroughCopy)
{
	auto service = DummyService(13);

	builder().registerInstance(service);

	ASSERT_EQ(13, container().resolve<DummyService>()._value);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceAsSharedPtr_WhenServiceInstanceRegisteredThroughCopy)
{
	auto service = DummyService(13);

	builder().registerInstance(service);

	ASSERT_EQ(13, container().resolve<std::shared_ptr<DummyService>>()->_value);
}

TEST_F(ServiceInstanceTest, ShouldThrowException_WhenResolvingServiceAsUniquePtr_AndServiceInstanceRegisteredThroughCopy)
{
	auto service = DummyService();

	builder().registerInstance(service);

	ASSERT_THROW(container().resolve<std::unique_ptr<DummyService>>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceAsPointer_WhenServiceInstanceRegisteredThroughMove)
{
	builder().registerInstance(DummyService(13));

	ASSERT_EQ(13, container().resolve<DummyService *>()->_value);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceAsReference_WhenServiceInstanceRegisteredThroughMove)
{
	builder().registerInstance(DummyService(13));

	ASSERT_EQ(13, container().resolve<DummyService &>()._value);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceAsCopy_WhenServiceInstanceRegisteredThroughMove)
{
	builder().registerInstance(DummyService(13));

	ASSERT_EQ(13, container().resolve<DummyService>()._value);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceAsSharedPtr_WhenServiceInstanceRegisteredThroughMove)
{
	builder().registerInstance(DummyService(13));

	ASSERT_EQ(13, container().resolve<std::shared_ptr<DummyService>>()->_value);
}

TEST_F(ServiceInstanceTest, ShouldThrowException_WhenResolvingServiceAsUniquePtr_AndServiceInstanceRegisteredThroughMove)
{
	builder().registerInstance(DummyService());

	ASSERT_THROW(container().resolve<std::unique_ptr<DummyService>>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceAsPointer_WhenServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<DummyService>();

	builder().registerInstance(service);

	ASSERT_EQ(service.get(), container().resolve<DummyService *>());
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceAsReference_WhenServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<DummyService>();

	builder().registerInstance(service);

	ASSERT_EQ(service.get(), &container().resolve<DummyService &>());
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceAsCopy_WhenServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<DummyService>(13);

	builder().registerInstance(service);

	ASSERT_EQ(13, container().resolve<DummyService>()._value);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceAsSharedPtr_WhenServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<DummyService>();

	builder().registerInstance(service);

	ASSERT_EQ(service.get(), container().resolve<std::shared_ptr<DummyService>>().get());
}

TEST_F(ServiceInstanceTest, ShouldThrowException_WhenResolvingServiceAsUniquePtr_AndServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<DummyService>();

	builder().registerInstance(service);

	ASSERT_THROW(container().resolve<std::unique_ptr<DummyService>>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceAsPointer_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	builder().registerInstance(std::make_unique<DummyService>(13));

	ASSERT_EQ(13, container().resolve<DummyService *>()->_value);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceAsReference_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	builder().registerInstance(std::make_unique<DummyService>(13));

	ASSERT_EQ(13, container().resolve<DummyService &>()._value);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceAsCopy_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	builder().registerInstance(std::make_unique<DummyService>(13));

	ASSERT_EQ(13, container().resolve<DummyService>()._value);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceAsSharedPtr_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	builder().registerInstance(std::make_unique<DummyService>(13));

	ASSERT_EQ(13, container().resolve<std::shared_ptr<DummyService>>()->_value);
}

TEST_F(ServiceInstanceTest, ShouldThrowException_WhenResolvingServiceAsUniquePtr_AndServiceInstanceRegisteredThroughUniquePtr)
{
	builder().registerInstance(std::make_unique<DummyService>(13));

	ASSERT_THROW(container().resolve<std::unique_ptr<DummyService>>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceInstanceTest, ShouldResolveCorrectServiceAsPointer_WhenServicesInstanceOfDifferentTypesRegistered)
{
	auto service1 = DummyService1();
	auto service2 = DummyService2();

	builder().registerInstance(&service1);
	builder().registerInstance(&service2);

	ASSERT_EQ(&service1, container().resolve<DummyService1 *>());
	ASSERT_EQ(&service2, container().resolve<DummyService2 *>());
}

TEST_F(ServiceInstanceTest, ShouldResolveCorrectServiceAsReference_WhenServicesInstanceOfDifferentTypesRegistered)
{
	auto service1 = DummyService1();
	auto service2 = DummyService2();

	builder().registerInstance(&service1);
	builder().registerInstance(&service2);

	ASSERT_EQ(&service1, &container().resolve<DummyService1 &>());
	ASSERT_EQ(&service2, &container().resolve<DummyService2 &>());
}

TEST_F(ServiceInstanceTest, ShouldResolveCorrectServiceAsCopy_WhenServicesInstanceOfDifferentTypesRegistered)
{
	auto service1 = DummyService1(13);
	auto service2 = DummyService2(14);

	builder().registerInstance(&service1);
	builder().registerInstance(&service2);

	ASSERT_EQ(13, container().resolve<DummyService1>()._value);
	ASSERT_EQ(14, container().resolve<DummyService2>()._value);
}

TEST_F(ServiceInstanceTest, ShouldResolveCorrectServiceAsSharedPtr_WhenServicesInstanceOfDifferentTypesRegistered)
{
	auto service1 = DummyService1();
	auto service2 = DummyService2();

	builder().registerInstance(&service1);
	builder().registerInstance(&service2);

	ASSERT_EQ(&service1, container().resolve<std::shared_ptr<DummyService1>>().get());
	ASSERT_EQ(&service2, container().resolve<std::shared_ptr<DummyService2>>().get());
}

TEST_F(ServiceInstanceTest, ShouldThrowException_WhenResolvingServiceOfOtherTypeThanRegistered)
{
	auto service1 = DummyService1();

	builder().registerInstance(&service1);

	ASSERT_THROW(container().resolve<DummyService2 *>(), DI::Error::ServiceNotRegistered);
}

TEST_F(ServiceInstanceTest, ShouldNotMove_WhenRegisteringServiceInstanceAsLValue)
{
	auto service = DummyService(13);

	builder().registerInstance(service);

	ASSERT_EQ(13, service._value);
}

TEST_F(ServiceInstanceTest, ShouldTakeOwnershipOfService_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	auto service = std::make_unique<DummyService>();

	builder().registerInstance(std::move(service));

	ASSERT_EQ(nullptr, service.get());
}

