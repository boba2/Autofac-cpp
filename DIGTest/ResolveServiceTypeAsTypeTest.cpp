#include "ContainerBaseTest.h"

namespace
{
	struct DummyService1 { virtual ~DummyService1() {} };
	struct SpecialDummyService : DummyService1 {};
}

using ResolveRegisteredServiceTypeAsTypeTest = ContainerBaseTest;

TEST_F(ResolveRegisteredServiceTypeAsTypeTest, ShouldResolveServiceAsBaseType_WhenServiceTypeRegisteredAliasedAsBaseType)
{
	builder()
		.registerType<SpecialDummyService>()
		.as<DummyService1>();

	ASSERT_TRUE(dynamic_cast<SpecialDummyService*>(container().resolve<std::shared_ptr<DummyService1>>().get()) != nullptr);
}