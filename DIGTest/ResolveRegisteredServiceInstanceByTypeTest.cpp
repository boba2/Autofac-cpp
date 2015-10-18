#include "ContainerBaseTest.h"

struct DummyService1 {};
struct DummyService2 {};
struct SpecialDummyService : DummyService1, DummyService2 {};

TEST_F(ContainerBaseTest, ShouldResolveServiceByBaseType_WhenServiceInstanceRegisteredAliasedAsBaseType)
{
	SpecialDummyService service;

	builder()
		.registerInstance(&service)
		.as<DummyService1>();

	ASSERT_EQ(&service, container().resolve<DummyService1 *>());
}

TEST_F(ContainerBaseTest, ShouldResolveServiceByAnyBaseType_WhenServiceInstanceRegisteredAliasedAsManyBaseTypes)
{
	SpecialDummyService service;

	builder()
		.registerInstance(&service)
		.as<DummyService1>()
		.as<DummyService2>();

	ASSERT_EQ(&service, container().resolve<DummyService1 *>());
	ASSERT_EQ(&service, container().resolve<DummyService2 *>());
}

TEST_F(ContainerBaseTest, ShouldThrowException_WhenResolvingServiceByItsType_AndServiceInstanceRegisteredOnlyWithAlias)
{
	SpecialDummyService service;

	builder()
		.registerInstance(&service)
		.as<DummyService1>();

	ASSERT_THROW(container().resolve<SpecialDummyService *>(), DI::Error::ServiceNotRegistered);
}

TEST_F(ContainerBaseTest, ShouldResolveServiceByItsType_WhenServiceInstanceRegisteredOnlyAliasedAsItsOwnType)
{
	SpecialDummyService service;

	builder()
		.registerInstance(&service)
		.as<SpecialDummyService>();

	ASSERT_EQ(&service, container().resolve<SpecialDummyService *>());
}

TEST_F(ContainerBaseTest, ShouldResolveServiceByVirtualBaseType_WhenServiceInstanceRegisteredWithAliasedAsVirtualBaseType)
{
//	SpecialDummyService service;
//
//	builder()
//		.registerInstance(&service)
//		.as<BaseDummyService>();
//
//	ASSERT_EQ(&service, dynamic_cast<SpecialDummyService *>(container().resolve<BaseDummyService *>()));
}