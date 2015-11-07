#include <stdafx.h>
#include "ContainerBaseTest.h"

namespace
{
	struct ServiceA {};
	struct ServiceB {};
	struct AbstractService { virtual ~AbstractService() = 0; };
}

using StaticAssertTest = ContainerBaseTest;

//TEST_F(StaticAssertTest, ShouldBreakStaticAssert_WhenRegisteringServiceTypeAliasedAsUnrelatedType)
//{
//	builder().registerType<ServiceA>().as<ServiceB>();
//}
//
//TEST_F(StaticAssertTest, ShouldBreakStaticAssert_WhenRegisteringServiceInstanceAliasedAsUnrelatedType)
//{
//	builder().registerInstance(ServiceA()).as<ServiceB>();
//}
//
//TEST_F(StaticAssertTest, ShouldBreakStaticAssert_WhenRegisteringServiceFactoryAliasedAsUnrelatedType)
//{
//	builder()
//		.registerFactory([] { return ServiceA(); })
//		.as<ServiceB>();
//}
//
//TEST_F(StaticAssertTest, ShouldBreakStaticAssert_WhenRegisteringAbstractServiceType)
//{
//	builder().registerType<AbstractService>();
//}
//
//TEST_F(StaticAssertTest, ShouldBreakStaticAssert_WhenRegisteringServiceOfDecoratedType)
//{
//	builder().registerType<ServiceA*>();
//}
