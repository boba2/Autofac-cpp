#include <stdafx.h>
#include "ContainerBaseTest.h"
#include "../DI/Error/ServiceNotRegistered.h"

namespace
{
	struct DummyService1 { virtual ~DummyService1() {} };
	struct DummyService2 {};
	struct SpecialDummyService : DummyService1 {};

	struct AbstractDummyService { virtual ~AbstractDummyService() {}; virtual void abstract() = 0; };
	struct ConcreteDummyService : AbstractDummyService { virtual void abstract() override {} };
}

using ServiceTypeAsTypeTest = ContainerBaseTest;

TEST_F(ServiceTypeAsTypeTest, ShouldBreakStaticAssert_WhenRegisteringServiceTypeAliasedAsUnrelatedType)
{
//	builder().registerType<DummyService1>().as<DummyService2>();
}

TEST_F(ServiceTypeAsTypeTest, ShouldResolveServiceAsBaseTypeAsPtr_WhenServiceTypeRegisteredAliasedAsBaseType)
{
	builder()
		.registerType<SpecialDummyService>()
		.as<DummyService1>()
		.autoManaged();

	ASSERT_TRUE(dynamic_cast<SpecialDummyService*>(container().resolve<DummyService1*>()) != nullptr);
}

TEST_F(ServiceTypeAsTypeTest, ShouldResolveServiceAsBaseTypeAsPtr_WhenServiceTypeRegisteredAliasedAsAbstractBaseType)
{
	builder()
		.registerType<ConcreteDummyService>()
		.as<AbstractDummyService>()
		.autoManaged();

	ASSERT_TRUE(dynamic_cast<ConcreteDummyService*>(container().resolve<AbstractDummyService*>()) != nullptr);
}

TEST_F(ServiceTypeAsTypeTest, ShouldResolveServiceAsBaseTypeAsConstRef_WhenServiceTypeRegisteredAliasedAsAbstractBaseType)
{
	builder()
		.registerType<ConcreteDummyService>()
		.as<AbstractDummyService>()
		.autoManaged();

	auto& service = container().resolve<AbstractDummyService>();

	ASSERT_TRUE(dynamic_cast<const ConcreteDummyService*>(&service) != nullptr);
}

TEST_F(ServiceTypeAsTypeTest, ShouldThrowException_WhenResolvingServiceAsItsType_AndServiceTypeRegisteredOnlyWithAlias)
{
	builder()
		.registerType<ConcreteDummyService>()
		.as<AbstractDummyService>()
		.autoManaged();

	ASSERT_THROW(container().resolve<ConcreteDummyService*>(), DI::Error::ServiceNotRegistered);
}

TEST_F(ServiceTypeAsTypeTest, ShouldResolveServiceAsItsType_WhenServiceTypeRegisteredWithAliasAndAsSelf)
{
	builder()
		.registerType<ConcreteDummyService>()
		.as<AbstractDummyService>()
		.asSelf()
		.autoManaged();

	ASSERT_TRUE(container().resolve<ConcreteDummyService*>() != nullptr);
}