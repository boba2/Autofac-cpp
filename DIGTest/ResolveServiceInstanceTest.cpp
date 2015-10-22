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

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceAsPointer_WhenServiceInstanceRegisteredThroughPointer)
{
	auto service = DummyService();

	builder().registerInstance(&service);

	ASSERT_EQ(&service, container().resolve<DummyService *>());
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceAsReference_WhenServiceInstanceRegisteredThroughPointer)
{
	auto service = DummyService();

	builder().registerInstance(&service);

	ASSERT_EQ(&service, &container().resolve<DummyService &>());
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceAsCopy_WhenServiceInstanceRegisteredThroughPointer)
{
	auto service = DummyService(13);

	builder().registerInstance(&service);

	ASSERT_EQ(13, container().resolve<DummyService>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceAsSharedPtr_WhenServiceInstanceRegisteredThroughPointer)
{
	auto service = DummyService();

	builder().registerInstance(&service);

	ASSERT_EQ(&service, container().resolve<std::shared_ptr<DummyService>>().get());
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldThrowException_WhenResolvingServiceAsUniquePtr_AndServiceInstanceRegisteredThroughPointer)
{
	auto service = DummyService();

	builder().registerInstance(&service);

	ASSERT_THROW(container().resolve<std::unique_ptr<DummyService>>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceAsPointer_WhenServiceInstanceRegisteredThroughCopy)
{
	auto service = DummyService(13);

	builder().registerInstance(service);

	ASSERT_EQ(13, container().resolve<DummyService *>()->_value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceAsReference_WhenServiceInstanceRegisteredThroughCopy)
{
	auto service = DummyService(13);

	builder().registerInstance(service);

	ASSERT_EQ(13, container().resolve<DummyService &>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceAsCopy_WhenServiceInstanceRegisteredThroughCopy)
{
	auto service = DummyService(13);

	builder().registerInstance(service);

	ASSERT_EQ(13, container().resolve<DummyService>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceAsSharedPtr_WhenServiceInstanceRegisteredThroughCopy)
{
	auto service = DummyService(13);

	builder().registerInstance(service);

	ASSERT_EQ(13, container().resolve<std::shared_ptr<DummyService>>()->_value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldThrowException_WhenResolvingServiceAsUniquePtr_AndServiceInstanceRegisteredThroughCopy)
{
	auto service = DummyService();

	builder().registerInstance(service);

	ASSERT_THROW(container().resolve<std::unique_ptr<DummyService>>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceAsPointer_WhenServiceInstanceRegisteredThroughMove)
{
	builder().registerInstance(DummyService(13));

	ASSERT_EQ(13, container().resolve<DummyService *>()->_value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceAsReference_WhenServiceInstanceRegisteredThroughMove)
{
	builder().registerInstance(DummyService(13));

	ASSERT_EQ(13, container().resolve<DummyService &>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceAsCopy_WhenServiceInstanceRegisteredThroughMove)
{
	builder().registerInstance(DummyService(13));

	ASSERT_EQ(13, container().resolve<DummyService>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceAsSharedPtr_WhenServiceInstanceRegisteredThroughMove)
{
	builder().registerInstance(DummyService(13));

	ASSERT_EQ(13, container().resolve<std::shared_ptr<DummyService>>()->_value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldThrowException_WhenResolvingServiceAsUniquePtr_AndServiceInstanceRegisteredThroughMove)
{
	builder().registerInstance(DummyService());

	ASSERT_THROW(container().resolve<std::unique_ptr<DummyService>>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceAsPointer_WhenServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<DummyService>();

	builder().registerInstance(service);

	ASSERT_EQ(service.get(), container().resolve<DummyService *>());
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceAsReference_WhenServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<DummyService>();

	builder().registerInstance(service);

	ASSERT_EQ(service.get(), &container().resolve<DummyService &>());
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceAsCopy_WhenServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<DummyService>(13);

	builder().registerInstance(service);

	ASSERT_EQ(13, container().resolve<DummyService>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceAsSharedPtr_WhenServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<DummyService>();

	builder().registerInstance(service);

	ASSERT_EQ(service.get(), container().resolve<std::shared_ptr<DummyService>>().get());
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldThrowException_WhenResolvingServiceAsUniquePtr_AndServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<DummyService>();

	builder().registerInstance(service);

	ASSERT_THROW(container().resolve<std::unique_ptr<DummyService>>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceAsPointer_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	builder().registerInstance(std::make_unique<DummyService>(13));

	ASSERT_EQ(13, container().resolve<DummyService *>()->_value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceAsReference_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	builder().registerInstance(std::make_unique<DummyService>(13));

	ASSERT_EQ(13, container().resolve<DummyService &>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceAsCopy_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	builder().registerInstance(std::make_unique<DummyService>(13));

	ASSERT_EQ(13, container().resolve<DummyService>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveServiceAsSharedPtr_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	builder().registerInstance(std::make_unique<DummyService>(13));

	ASSERT_EQ(13, container().resolve<std::shared_ptr<DummyService>>()->_value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldThrowException_WhenResolvingServiceAsUniquePtr_AndServiceInstanceRegisteredThroughUniquePtr)
{
	builder().registerInstance(std::make_unique<DummyService>(13));

	ASSERT_THROW(container().resolve<std::unique_ptr<DummyService>>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveCorrectServiceAsPointer_WhenServicesInstanceOfDifferentTypesRegistered)
{
	auto service1 = DummyService1();
	auto service2 = DummyService2();

	builder().registerInstance(&service1);
	builder().registerInstance(&service2);

	ASSERT_EQ(&service1, container().resolve<DummyService1 *>());
	ASSERT_EQ(&service2, container().resolve<DummyService2 *>());
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveCorrectServiceAsReference_WhenServicesInstanceOfDifferentTypesRegistered)
{
	auto service1 = DummyService1();
	auto service2 = DummyService2();

	builder().registerInstance(&service1);
	builder().registerInstance(&service2);

	ASSERT_EQ(&service1, &container().resolve<DummyService1 &>());
	ASSERT_EQ(&service2, &container().resolve<DummyService2 &>());
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveCorrectServiceAsCopy_WhenServicesInstanceOfDifferentTypesRegistered)
{
	auto service1 = DummyService1(13);
	auto service2 = DummyService2(14);

	builder().registerInstance(&service1);
	builder().registerInstance(&service2);

	ASSERT_EQ(13, container().resolve<DummyService1>()._value);
	ASSERT_EQ(14, container().resolve<DummyService2>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldResolveCorrectServiceAsSharedPtr_WhenServicesInstanceOfDifferentTypesRegistered)
{
	auto service1 = DummyService1();
	auto service2 = DummyService2();

	builder().registerInstance(&service1);
	builder().registerInstance(&service2);

	ASSERT_EQ(&service1, container().resolve<std::shared_ptr<DummyService1>>().get());
	ASSERT_EQ(&service2, container().resolve<std::shared_ptr<DummyService2>>().get());
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldThrowException_WhenResolvingServiceOfOtherTypeThanRegistered)
{
	auto service1 = DummyService1();

	builder().registerInstance(&service1);

	ASSERT_THROW(container().resolve<DummyService2 *>(), DI::Error::ServiceNotRegistered);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldNotMove_WhenRegisteringServiceInstanceAsLValue)
{
	auto service = DummyService(13);

	builder().registerInstance(service);

	ASSERT_EQ(13, service._value);
}

TEST_F(ResolveRegisteredServiceInstanceTest, ShouldTakeOwnershipOfService_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	auto service = std::make_unique<DummyService>();

	builder().registerInstance(std::move(service));

	ASSERT_EQ(nullptr, service.get());
}

