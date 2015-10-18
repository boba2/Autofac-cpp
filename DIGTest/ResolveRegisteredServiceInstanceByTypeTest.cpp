#include "ContainerBaseTest.h"
#include "../DITest/Error/ServiceInstanceNotResolvableAs.h"

struct DummyService1 { int _value; };
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

TEST_F(ContainerBaseTest, ShouldResolveServiceByItsType_WhenServiceInstanceRegisteredWithAliasAndAsSelf)
{
	SpecialDummyService service;

	builder()
		.registerInstance(&service)
		.as<DummyService1>()
		.asSelf();

	ASSERT_EQ(&service, container().resolve<SpecialDummyService *>());
}

TEST_F(ContainerBaseTest, ShouldResolveServiceByBaseType_WhenServiceInstanceRegisteredAliasedAsBaseTypeAndAsSelf)
{
	SpecialDummyService service;

	builder()
		.registerInstance(&service)
		.as<DummyService1>()
		.asSelf();

	ASSERT_EQ(&service, container().resolve<DummyService1 *>());
}

TEST_F(ContainerBaseTest, ShouldResolveServiceByItsType_WhenServiceInstanceRegisteredOnlyAsSelf)
{
	SpecialDummyService service;

	builder()
		.registerInstance(&service)
		.asSelf();

	ASSERT_EQ(&service, container().resolve<SpecialDummyService *>());
}

TEST_F(ContainerBaseTest, ShouldResolveServiceByBaseTypeAsCopy_WhenServiceInstanceRegisteredAliasedAsBaseType)
{
	SpecialDummyService service;
	service._value = 13;

	builder()
		.registerInstance(&service)
		.as<DummyService1>();

	ASSERT_EQ(13, container().resolve<DummyService1>()._value);
}

TEST_F(ContainerBaseTest, ShouldResolveServiceByBaseTypeAsReference_WhenServiceInstanceRegisteredAliasedAsBaseType)
{
	SpecialDummyService service;

	builder()
		.registerInstance(&service)
		.as<DummyService1>();

	ASSERT_EQ(&service, &container().resolve<DummyService1 &>());
}

TEST_F(ContainerBaseTest, ShouldResolveServiceByBaseTypeAsSharedPtr_WhenServiceInstanceRegisteredAliasedAsBaseType)
{
	SpecialDummyService service;

	builder()
		.registerInstance(&service)
		.as<DummyService1>();

	ASSERT_EQ(&service, container().resolve<std::shared_ptr<DummyService1>>().get());
}

TEST_F(ContainerBaseTest, ShouldThrowException_WhenResolvingServiceByBaseTypeAsUniquePtr_WhenServiceInstanceRegisteredAliasedAsBaseType)
{
	SpecialDummyService service;

	builder()
		.registerInstance(&service)
		.as<DummyService1>();

	ASSERT_THROW(container().resolve<std::unique_ptr<DummyService1>>(), DI::Error::ServiceInstanceNotResolvableAs);
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