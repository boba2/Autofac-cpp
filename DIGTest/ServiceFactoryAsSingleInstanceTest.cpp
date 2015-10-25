#include <stdafx.h>
#include "ContainerBaseTest.h"

using ServiceFactoryAsSingleInstance = ContainerBaseTest;

namespace
{
	struct ServiceA {};
}

TEST_F(ServiceFactoryAsSingleInstance, ShouldResolveSingleServiceAsPtr_WhenServiceFactoryRegisteredAsSingleInstance)
{
	builder()
		.registerFactory([] { return ServiceA(); })
		.singleInstance();

	auto service1 = container().resolve<ServiceA*>();
	auto service2 = container().resolve<ServiceA*>();

	ASSERT_EQ(service1, service2);
}

TEST_F(ServiceFactoryAsSingleInstance, ShouldResolveSingleServiceAsRef_WhenServiceFactoryRegisteredAsSingleInstance)
{
	builder()
		.registerFactory([] { return ServiceA(); })
		.singleInstance();

	auto& service1 = container().resolve<ServiceA&>();
	auto& service2 = container().resolve<ServiceA&>();

	ASSERT_EQ(&service1, &service2);
}

TEST_F(ServiceFactoryAsSingleInstance, ShouldResolveSingleServiceAsSharedPtr_WhenServiceFactoryRegisteredAsSingleInstance)
{
	builder()
		.registerFactory([] { return ServiceA(); })
		.singleInstance();

	auto service1 = container().resolve<std::shared_ptr<ServiceA>>();
	auto service2 = container().resolve<std::shared_ptr<ServiceA>>();

	ASSERT_EQ(service1, service2);
}

TEST_F(ServiceFactoryAsSingleInstance, ShouldThrowException_WhenResolvingSingleServiceAsUniquePtr)
{
	builder()
		.registerFactory([] { return ServiceA(); })
		.singleInstance();

	ASSERT_THROW(container().resolve<std::unique_ptr<ServiceA>>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceFactoryAsSingleInstance, ShouldResolveSingleServiceAsBaseType_WhenServiceFactoryRegisteredAliasedAsBaseType_AndAsSingleInstance)
{
//	struct BaseService1 { virtual ~BaseService1() {} };
//	struct BaseService2 { virtual ~BaseService2() {} };
//	struct SpecialService : BaseService1, BaseService2 {};
//
//	struct SpecialServiceA : ServiceA {};
//	builder()
//		.registerFactory([] { return SpecialService(); })
//		.as<BaseService1>()
//		.as<BaseService2>()
//		.singleInstance();
//
//	auto service1 = container().resolve<BaseService1*>();
//	auto service2 = container().resolve<BaseService2*>();
//
//	ASSERT_EQ(dynamic_cast<SpecialService*>(service1), dynamic_cast<SpecialService*>(service2));
}