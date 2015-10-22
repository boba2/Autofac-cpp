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

using ResolveRegisteredServiceInstanceTest = ContainerBaseTest;

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByPointer_WhenServiceInstanceRegisteredThroughPointer)
{
	auto service = DummyService();

	builder().registerInstance(&service);

	ASSERT_EQ(&service, container().resolve<DummyService *>());
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByReference_WhenServiceInstanceRegisteredThroughPointer)
{
	auto service = DummyService();

	builder().registerInstance(&service);

	ASSERT_EQ(&service, &container().resolve<DummyService &>());
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByCopy_WhenServiceInstanceRegisteredThroughPointer)
{
	auto service = DummyService(13);

	builder().registerInstance(&service);

	ASSERT_EQ(13, container().resolve<DummyService>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceBySharedPtr_WhenServiceInstanceRegisteredThroughPointer)
{
	auto service = DummyService();

	builder().registerInstance(&service);

	ASSERT_EQ(&service, container().resolve<std::shared_ptr<DummyService>>().get());
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldThrowException_WhenResolvingServiceByUniquePtr_AndServiceInstanceRegisteredThroughPointer)
{
	auto service = DummyService();

	builder().registerInstance(&service);

	ASSERT_THROW(container().resolve<std::unique_ptr<DummyService>>(), DI::Error::ServiceInstanceNotResolvableAs);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByPointer_WhenServiceInstanceRegisteredThroughCopy)
{
	auto service = DummyService(13);

	builder().registerInstance(service);

	ASSERT_EQ(13, container().resolve<DummyService *>()->_value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByReference_WhenServiceInstanceRegisteredThroughCopy)
{
	auto service = DummyService(13);

	builder().registerInstance(service);

	ASSERT_EQ(13, container().resolve<DummyService &>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByCopy_WhenServiceInstanceRegisteredThroughCopy)
{
	auto service = DummyService(13);

	builder().registerInstance(service);

	ASSERT_EQ(13, container().resolve<DummyService>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceBySharedPtr_WhenServiceInstanceRegisteredThroughCopy)
{
	auto service = DummyService(13);

	builder().registerInstance(service);

	ASSERT_EQ(13, container().resolve<std::shared_ptr<DummyService>>()->_value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldThrowException_WhenResolvingServiceByUniquePtr_AndServiceInstanceRegisteredThroughCopy)
{
	auto service = DummyService();

	builder().registerInstance(service);

	ASSERT_THROW(container().resolve<std::unique_ptr<DummyService>>(), DI::Error::ServiceInstanceNotResolvableAs);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByPointer_WhenServiceInstanceRegisteredThroughMove)
{
	builder().registerInstance(DummyService(13));

	ASSERT_EQ(13, container().resolve<DummyService *>()->_value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByReference_WhenServiceInstanceRegisteredThroughMove)
{
	builder().registerInstance(DummyService(13));

	ASSERT_EQ(13, container().resolve<DummyService &>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByCopy_WhenServiceInstanceRegisteredThroughMove)
{
	builder().registerInstance(DummyService(13));

	ASSERT_EQ(13, container().resolve<DummyService>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceBySharedPtr_WhenServiceInstanceRegisteredThroughMove)
{
	builder().registerInstance(DummyService(13));

	ASSERT_EQ(13, container().resolve<std::shared_ptr<DummyService>>()->_value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldThrowException_WhenResolvingServiceByUniquePtr_AndServiceInstanceRegisteredThroughMove)
{
	builder().registerInstance(DummyService());

	ASSERT_THROW(container().resolve<std::unique_ptr<DummyService>>(), DI::Error::ServiceInstanceNotResolvableAs);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByPointer_WhenServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<DummyService>();

	builder().registerInstance(service);

	ASSERT_EQ(service.get(), container().resolve<DummyService *>());
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByReference_WhenServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<DummyService>();

	builder().registerInstance(service);

	ASSERT_EQ(service.get(), &container().resolve<DummyService &>());
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByCopy_WhenServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<DummyService>(13);

	builder().registerInstance(service);

	ASSERT_EQ(13, container().resolve<DummyService>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceBySharedPtr_WhenServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<DummyService>();

	builder().registerInstance(service);

	ASSERT_EQ(service.get(), container().resolve<std::shared_ptr<DummyService>>().get());
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldThrowException_WhenResolvingServiceByUniquePtr_AndServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<DummyService>();

	builder().registerInstance(service);

	ASSERT_THROW(container().resolve<std::unique_ptr<DummyService>>(), DI::Error::ServiceInstanceNotResolvableAs);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByPointer_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	builder().registerInstance(std::make_unique<DummyService>(13));

	ASSERT_EQ(13, container().resolve<DummyService *>()->_value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByReference_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	builder().registerInstance(std::make_unique<DummyService>(13));

	ASSERT_EQ(13, container().resolve<DummyService &>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceByCopy_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	builder().registerInstance(std::make_unique<DummyService>(13));

	ASSERT_EQ(13, container().resolve<DummyService>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceBySharedPtr_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	builder().registerInstance(std::make_unique<DummyService>(13));

	ASSERT_EQ(13, container().resolve<std::shared_ptr<DummyService>>()->_value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldThrowException_WhenResolvingServiceByUniquePtr_AndServiceInstanceRegisteredThroughUniquePtr)
{
	builder().registerInstance(std::make_unique<DummyService>(13));

	ASSERT_THROW(container().resolve<std::unique_ptr<DummyService>>(), DI::Error::ServiceInstanceNotResolvableAs);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveCorrectServiceByPointer_WhenServicesInstanceOfDifferentTypesRegistered)
{
	DummyService1 service1;
	DummyService2 service2;

	builder().registerInstance(&service1);
	builder().registerInstance(&service2);

	ASSERT_EQ(&service1, container().resolve<DummyService1 *>());
	ASSERT_EQ(&service2, container().resolve<DummyService2 *>());
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveCorrectServiceByReference_WhenServicesInstanceOfDifferentTypesRegistered)
{
	DummyService1 service1;
	DummyService2 service2;

	builder().registerInstance(&service1);
	builder().registerInstance(&service2);

	ASSERT_EQ(&service1, &container().resolve<DummyService1 &>());
	ASSERT_EQ(&service2, &container().resolve<DummyService2 &>());
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveCorrectServiceByCopy_WhenServicesInstanceOfDifferentTypesRegistered)
{
	DummyService1 service1(13);
	DummyService2 service2(14);

	builder().registerInstance(&service1);
	builder().registerInstance(&service2);

	ASSERT_EQ(13, container().resolve<DummyService1>()._value);
	ASSERT_EQ(14, container().resolve<DummyService2>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveCorrectServiceBySharedPtr_WhenServicesInstanceOfDifferentTypesRegistered)
{
	DummyService1 service1;
	DummyService2 service2;

	builder().registerInstance(&service1);
	builder().registerInstance(&service2);

	ASSERT_EQ(&service1, container().resolve<std::shared_ptr<DummyService1>>().get());
	ASSERT_EQ(&service2, container().resolve<std::shared_ptr<DummyService2>>().get());
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldThrowException_WhenResolvingServiceOfOtherTypeThanRegistered)
{
	DummyService1 service1;

	builder().registerInstance(&service1);

	ASSERT_THROW(container().resolve<DummyService2 *>(), DI::Error::ServiceNotRegistered);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldNotMove_WhenRegisteringServiceInstanceAsLValue)
{
	DummyService service(13);

	builder().registerInstance(service);

	ASSERT_EQ(13, service._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldTakeOwnershipOfService_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	auto service = std::make_unique<DummyService>();

	builder().registerInstance(std::move(service));

	ASSERT_EQ(nullptr, service.get());
}

