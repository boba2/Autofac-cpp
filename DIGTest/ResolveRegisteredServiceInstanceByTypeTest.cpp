#include "ContainerBaseTest.h"

struct DummyService1 {};
struct DummyService2 {};
struct SpecialDummyService : DummyService1, DummyService2 {};

TEST_F(ContainerBaseTest, ShouldResolveServiceByBaseType_WhenServiceInstanceRegisteredWithAliasForBaseType)
{
	SpecialDummyService service;

	builder()
		.registerInstance(&service)
		.as<DummyService1>();

	ASSERT_EQ(&service, container().resolve<DummyService1 *>());
}

TEST_F(ContainerBaseTest, ShouldResolveServiceByAnyBaseType_WhenServiceInstanceRegisteredWithAliasesForManyBaseTypes)
{
	SpecialDummyService service;

	builder()
		.registerInstance(&service)
		.as<DummyService1>()
		.as<DummyService2>();

	ASSERT_EQ(&service, container().resolve<DummyService1 *>());
	ASSERT_EQ(&service, container().resolve<DummyService2 *>());
}

TEST_F(ContainerBaseTest, ShouldResolveServiceByVirtualBaseType_WhenServiceInstanceRegisteredWithAliasForVirtualBaseType)
{
//	SpecialDummyService service;
//
//	builder()
//		.registerInstance(&service)
//		.as<BaseDummyService>();
//
//	ASSERT_EQ(&service, dynamic_cast<SpecialDummyService *>(container().resolve<BaseDummyService *>()));
}