#include <stdafx.h>

#include "ContainerBaseTest.h"
#include "../DI/Error/ServiceNotRegistered.h"

namespace
{
	class ServiceA
	{
	public:
		int _value;
		explicit ServiceA(const int value = 0) : _value(value) {}
		ServiceA(const ServiceA &other) = default;
		ServiceA(ServiceA &&other) = default;
		ServiceA &operator=(const ServiceA &other) = default;
		ServiceA &operator=(ServiceA &&other) = default;
	};

	struct ServiceB
	{
		int _value;
		explicit ServiceB(const int value = 0) : _value(value) {}
	};

	struct ServiceC
	{
		int _value;
		explicit ServiceC(const int value = 0) : _value(value) {}
	};
}

using ServiceInstanceTest = ContainerBaseTest;

TEST_F(ServiceInstanceTest, ShouldResolveServiceBsPointer_WhenServiceInstanceRegisteredThroughPointer)
{
	auto service = ServiceA();

	builder().registerInstance(&service);

	auto resolved = container().resolve<ServiceA *>();

	ASSERT_EQ(&service, resolved);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceBsReference_WhenServiceInstanceRegisteredThroughPointer)
{
	auto service = ServiceA();

	builder().registerInstance(&service);

	auto& resolved = container().resolve<ServiceA &>();

	ASSERT_EQ(&service, &resolved);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceBsCopy_WhenServiceInstanceRegisteredThroughPointer)
{
	auto service = ServiceA(13);

	builder().registerInstance(&service);

	auto resolved = container().resolve<ServiceA>();

	ASSERT_EQ(13, resolved._value);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceBsSharedPtr_WhenServiceInstanceRegisteredThroughPointer)
{
	auto service = ServiceA();

	builder().registerInstance(&service);

	auto resolved = container().resolve<std::shared_ptr<ServiceA>>();

	ASSERT_EQ(&service, resolved.get());
}

TEST_F(ServiceInstanceTest, ShouldThrowException_WhenResolvingServiceBsUniquePtr_AndServiceInstanceRegisteredThroughPointer)
{
	auto service = ServiceA();

	builder().registerInstance(&service);

	ASSERT_THROW(container().resolve<std::unique_ptr<ServiceA>>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceBsPointer_WhenServiceInstanceRegisteredThroughCopy)
{
	auto service = ServiceA(13);

	builder().registerInstance(service);

	auto resolved = container().resolve<ServiceA *>();

	ASSERT_EQ(13, resolved->_value);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceBsReference_WhenServiceInstanceRegisteredThroughCopy)
{
	auto service = ServiceA(13);

	builder().registerInstance(service);

	auto& resolved = container().resolve<ServiceA &>();

	ASSERT_EQ(13, resolved._value);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceBsCopy_WhenServiceInstanceRegisteredThroughCopy)
{
	auto service = ServiceA(13);

	builder().registerInstance(service);

	auto resolved = container().resolve<ServiceA>();

	ASSERT_EQ(13, resolved._value);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceBsSharedPtr_WhenServiceInstanceRegisteredThroughCopy)
{
	auto service = ServiceA(13);

	builder().registerInstance(service);

	auto resolved = container().resolve<std::shared_ptr<ServiceA>>();

	ASSERT_EQ(13, resolved->_value);
}

TEST_F(ServiceInstanceTest, ShouldThrowException_WhenResolvingServiceBsUniquePtr_AndServiceInstanceRegisteredThroughCopy)
{
	auto service = ServiceA();

	builder().registerInstance(service);

	ASSERT_THROW(container().resolve<std::unique_ptr<ServiceA>>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceBsPointer_WhenServiceInstanceRegisteredThroughMove)
{
	builder().registerInstance(ServiceA(13));

	auto resolved = container().resolve<ServiceA *>();

	ASSERT_EQ(13, resolved->_value);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceBsReference_WhenServiceInstanceRegisteredThroughMove)
{
	builder().registerInstance(ServiceA(13));

	auto& resolved = container().resolve<ServiceA &>();

	ASSERT_EQ(13, resolved._value);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceBsCopy_WhenServiceInstanceRegisteredThroughMove)
{
	builder().registerInstance(ServiceA(13));

	auto resolved = container().resolve<ServiceA>();

	ASSERT_EQ(13, resolved._value);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceBsSharedPtr_WhenServiceInstanceRegisteredThroughMove)
{
	builder().registerInstance(ServiceA(13));

	auto resolved = container().resolve<std::shared_ptr<ServiceA>>();

	ASSERT_EQ(13, resolved->_value);
}

TEST_F(ServiceInstanceTest, ShouldThrowException_WhenResolvingServiceBsUniquePtr_AndServiceInstanceRegisteredThroughMove)
{
	builder().registerInstance(ServiceA());

	ASSERT_THROW(container().resolve<std::unique_ptr<ServiceA>>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceBsPointer_WhenServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<ServiceA>();

	builder().registerInstance(service);

	auto resolved = container().resolve<ServiceA *>();

	ASSERT_EQ(service.get(), resolved);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceBsReference_WhenServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<ServiceA>();

	builder().registerInstance(service);

	auto& resolved = container().resolve<ServiceA &>();

	ASSERT_EQ(service.get(), &resolved);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceBsCopy_WhenServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<ServiceA>(13);

	builder().registerInstance(service);

	auto resolved = container().resolve<ServiceA>();

	ASSERT_EQ(13, resolved._value);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceBsSharedPtr_WhenServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<ServiceA>();

	builder().registerInstance(service);

	auto resolved = container().resolve<std::shared_ptr<ServiceA>>();

	ASSERT_EQ(service.get(), resolved.get());
}

TEST_F(ServiceInstanceTest, ShouldThrowException_WhenResolvingServiceBsUniquePtr_AndServiceInstanceRegisteredThroughSharedPtr)
{
	auto service = std::make_shared<ServiceA>();

	builder().registerInstance(service);

	ASSERT_THROW(container().resolve<std::unique_ptr<ServiceA>>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceBsPointer_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	builder().registerInstance(std::make_unique<ServiceA>(13));

	auto resolved = container().resolve<ServiceA *>();

	ASSERT_EQ(13, resolved->_value);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceBsReference_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	builder().registerInstance(std::make_unique<ServiceA>(13));

	auto& resolved = container().resolve<ServiceA &>();

	ASSERT_EQ(13, resolved._value);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceBsCopy_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	builder().registerInstance(std::make_unique<ServiceA>(13));

	auto resolved = container().resolve<ServiceA>();

	ASSERT_EQ(13, resolved._value);
}

TEST_F(ServiceInstanceTest, ShouldResolveServiceBsSharedPtr_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	builder().registerInstance(std::make_unique<ServiceA>(13));

	auto resolved = container().resolve<std::shared_ptr<ServiceA>>();

	ASSERT_EQ(13, resolved->_value);
}

TEST_F(ServiceInstanceTest, ShouldThrowException_WhenResolvingServiceBsUniquePtr_AndServiceInstanceRegisteredThroughUniquePtr)
{
	builder().registerInstance(std::make_unique<ServiceA>(13));

	ASSERT_THROW(container().resolve<std::unique_ptr<ServiceA>>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceInstanceTest, ShouldResolveCorrectServiceBsPointer_WhenServicesInstanceOfDifferentTypesRegistered)
{
	auto service1 = ServiceB();
	auto service2 = ServiceC();

	builder().registerInstance(&service1);
	builder().registerInstance(&service2);

	auto resolvedB = container().resolve<ServiceB *>();
	auto resolvedC = container().resolve<ServiceC *>();

	ASSERT_EQ(&service1, resolvedB);
	ASSERT_EQ(&service2, resolvedC);
}

TEST_F(ServiceInstanceTest, ShouldResolveCorrectServiceBsReference_WhenServicesInstanceOfDifferentTypesRegistered)
{
	auto service1 = ServiceB();
	auto service2 = ServiceC();

	builder().registerInstance(&service1);
	builder().registerInstance(&service2);

	auto& resolvedB = container().resolve<ServiceB &>();
	auto& resolvedC = container().resolve<ServiceC &>();

	ASSERT_EQ(&service1, &resolvedB);
	ASSERT_EQ(&service2, &resolvedC);
}

TEST_F(ServiceInstanceTest, ShouldResolveCorrectServiceBsCopy_WhenServicesInstanceOfDifferentTypesRegistered)
{
	auto service1 = ServiceB(13);
	auto service2 = ServiceC(14);

	builder().registerInstance(&service1);
	builder().registerInstance(&service2);

	auto resolvedB = container().resolve<ServiceB>();
	auto resolvedC = container().resolve<ServiceC>();

	ASSERT_EQ(13, resolvedB._value);
	ASSERT_EQ(14, resolvedC._value);
}

TEST_F(ServiceInstanceTest, ShouldResolveCorrectServiceBsSharedPtr_WhenServicesInstanceOfDifferentTypesRegistered)
{
	auto service1 = ServiceB();
	auto service2 = ServiceC();

	builder().registerInstance(&service1);
	builder().registerInstance(&service2);

	auto resolvedB = container().resolve<std::shared_ptr<ServiceB>>();
	auto resolvedC = container().resolve<std::shared_ptr<ServiceC>>();

	ASSERT_EQ(&service1, resolvedB.get());
	ASSERT_EQ(&service2, resolvedC.get());
}

TEST_F(ServiceInstanceTest, ShouldThrowException_WhenResolvingServiceOfOtherTypeThanRegistered)
{
	auto service1 = ServiceB();

	builder().registerInstance(&service1);

	ASSERT_THROW(container().resolve<ServiceC *>(), DI::Error::ServiceNotRegistered);
}

TEST_F(ServiceInstanceTest, ShouldNotMove_WhenRegisteringServiceInstanceAsLValue)
{
	auto service = ServiceA(13);

	builder().registerInstance(service);

	ASSERT_EQ(13, service._value);
}

TEST_F(ServiceInstanceTest, ShouldTakeOwnershipOfService_WhenServiceInstanceRegisteredThroughUniquePtr)
{
	auto service = std::make_unique<ServiceA>();

	builder().registerInstance(std::move(service));

	ASSERT_EQ(nullptr, service.get());
}

