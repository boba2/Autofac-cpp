#include <stdafx.h>

#include "ContainerBaseTest.h"

namespace
{
	struct DummyService1 { virtual ~DummyService1() {} };
	struct DummyService2 {};
	struct SpecialDummyService : DummyService1 {};

	struct AbstractDummyService { virtual ~AbstractDummyService() {}; virtual void abstract() = 0; };
	struct ConcreteDummyService : AbstractDummyService { virtual void abstract() override {} };
}

using ResolveRegisteredServiceTypeAsTypeTest = ContainerBaseTest;

TEST_F(ResolveRegisteredServiceTypeAsTypeTest, ShouldBreakStaticAssert_WhenRegisteringServiceTypeAliasedAsUnrelatedType)
{
//	builder().registerType<DummyService1>().as<DummyService2>();
}

TEST_F(ResolveRegisteredServiceTypeAsTypeTest, ShouldResolveServiceAsBaseTypeAsPtr_WhenServiceTypeRegisteredAliasedAsBaseType)
{
	builder()
		.registerType<SpecialDummyService>()
		.as<DummyService1>()
		.autoManaged();

	ASSERT_TRUE(dynamic_cast<SpecialDummyService*>(container().resolve<DummyService1*>()) != nullptr);
}

TEST_F(ResolveRegisteredServiceTypeAsTypeTest, ShouldResolveServiceAsBaseTypeAsPtr_WhenServiceTypeRegisteredAliasedAsAbstractBaseType)
{
	builder()
		.registerType<ConcreteDummyService>()
		.as<AbstractDummyService>()
		.autoManaged();

	ASSERT_TRUE(dynamic_cast<ConcreteDummyService*>(container().resolve<AbstractDummyService*>()) != nullptr);
}

TEST_F(ResolveRegisteredServiceTypeAsTypeTest, ShouldResolveServiceAsBaseTypeAsConstRef_WhenServiceTypeRegisteredAliasedAsAbstractBaseType)
{
	builder()
		.registerType<ConcreteDummyService>()
		.as<AbstractDummyService>()
		.autoManaged();

	auto& service = container().resolve<AbstractDummyService>();

	ASSERT_TRUE(dynamic_cast<const ConcreteDummyService*>(&service) != nullptr);
}