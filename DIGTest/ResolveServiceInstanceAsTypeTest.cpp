#include "ContainerBaseTest.h"
#include "../DI/Error/ServiceInstanceNotResolvableAs.h"
#include "../DI/Error/ServiceNotRegistered.h"

namespace
{
	struct DummyService1 { int _value; };
	struct DummyService2 {};
	struct SpecialDummyService : DummyService1, DummyService2 {};
}

using ResolveRegisteredServiceInstanceAsTypeTest = ContainerBaseTest;

TEST_F(ResolveRegisteredServiceInstanceAsTypeTest, ShouldResolveServiceAsBaseType_WhenServiceInstanceRegisteredAliasedAsBaseType)
{
	SpecialDummyService service;

	builder()
		.registerInstance(&service)
		.as<DummyService1>();

	ASSERT_EQ(&service, container().resolve<DummyService1 *>());
}

TEST_F(ResolveRegisteredServiceInstanceAsTypeTest, ShouldResolveServiceAsAnyBaseType_WhenServiceInstanceRegisteredAliasedAsManyBaseTypes)
{
	SpecialDummyService service;

	builder()
		.registerInstance(&service)
		.as<DummyService1>()
		.as<DummyService2>();

	ASSERT_EQ(&service, container().resolve<DummyService1 *>());
	ASSERT_EQ(&service, container().resolve<DummyService2 *>());
}

TEST_F(ResolveRegisteredServiceInstanceAsTypeTest, ShouldThrowException_WhenResolvingServiceAsItsType_AndServiceInstanceRegisteredOnlyWithAlias)
{
	SpecialDummyService service;

	builder()
		.registerInstance(&service)
		.as<DummyService1>();

	ASSERT_THROW(container().resolve<SpecialDummyService *>(), DI::Error::ServiceNotRegistered);
}

TEST_F(ResolveRegisteredServiceInstanceAsTypeTest, ShouldResolveServiceAsItsType_WhenServiceInstanceRegisteredOnlyAliasedAsItsOwnType)
{
	SpecialDummyService service;

	builder()
		.registerInstance(&service)
		.as<SpecialDummyService>();

	ASSERT_EQ(&service, container().resolve<SpecialDummyService *>());
}

TEST_F(ResolveRegisteredServiceInstanceAsTypeTest, ShouldResolveServiceAsItsType_WhenServiceInstanceRegisteredWithAliasAndAsSelf)
{
	SpecialDummyService service;

	builder()
		.registerInstance(&service)
		.as<DummyService1>()
		.asSelf();

	ASSERT_EQ(&service, container().resolve<SpecialDummyService *>());
}

TEST_F(ResolveRegisteredServiceInstanceAsTypeTest, ShouldResolveServiceAsBaseType_WhenServiceInstanceRegisteredAliasedAsBaseTypeAndAsSelf)
{
	SpecialDummyService service;

	builder()
		.registerInstance(&service)
		.as<DummyService1>()
		.asSelf();

	ASSERT_EQ(&service, container().resolve<DummyService1 *>());
}

TEST_F(ResolveRegisteredServiceInstanceAsTypeTest, ShouldResolveServiceAsItsType_WhenServiceInstanceRegisteredOnlyAsSelf)
{
	SpecialDummyService service;

	builder()
		.registerInstance(&service)
		.asSelf();

	ASSERT_EQ(&service, container().resolve<SpecialDummyService *>());
}

TEST_F(ResolveRegisteredServiceInstanceAsTypeTest, ShouldResolveServiceAsBaseTypeAsCopy_WhenServiceInstanceRegisteredAliasedAsBaseType)
{
	SpecialDummyService service;
	service._value = 13;

	builder()
		.registerInstance(&service)
		.as<DummyService1>();

	ASSERT_EQ(13, container().resolve<DummyService1>()._value);
}

TEST_F(ResolveRegisteredServiceInstanceAsTypeTest, ShouldResolveServiceAsBaseTypeAsReference_WhenServiceInstanceRegisteredAliasedAsBaseType)
{
	SpecialDummyService service;

	builder()
		.registerInstance(&service)
		.as<DummyService1>();

	ASSERT_EQ(&service, &container().resolve<DummyService1 &>());
}

TEST_F(ResolveRegisteredServiceInstanceAsTypeTest, ShouldResolveServiceAsBaseTypeAsSharedPtr_WhenServiceInstanceRegisteredAliasedAsBaseType)
{
	SpecialDummyService service;

	builder()
		.registerInstance(&service)
		.as<DummyService1>();

	ASSERT_EQ(&service, container().resolve<std::shared_ptr<DummyService1>>().get());
}

TEST_F(ResolveRegisteredServiceInstanceAsTypeTest, ShouldThrowException_WhenResolvingServiceAsBaseTypeAsUniquePtr_WhenServiceInstanceRegisteredAliasedAsBaseType)
{
	SpecialDummyService service;

	builder()
		.registerInstance(&service)
		.as<DummyService1>();

	ASSERT_THROW(container().resolve<std::unique_ptr<DummyService1>>(), DI::Error::ServiceInstanceNotResolvableAs);
}

TEST_F(ResolveRegisteredServiceInstanceAsTypeTest, ShouldBreakStaticAssert_WhenRegisteringAliasedAsUnrelatedType)
{
//	builder()
//		.registerInstance(DummyService1())
//		.as<DummyService2>();
}

TEST_F(ResolveRegisteredServiceInstanceAsTypeTest, ShouldResolveServiceAsVirtualBaseType_WhenServiceInstanceRegisteredWithAliasedAsVirtualBaseType)
{
//	SpecialDummyService service;
//
//	builder()
//		.registerInstance(&service)
//		.as<BaseDummyService>();
//
//	ASSERT_EQ(&service, dynamic_cast<SpecialDummyService *>(container().resolve<BaseDummyService *>()));
}