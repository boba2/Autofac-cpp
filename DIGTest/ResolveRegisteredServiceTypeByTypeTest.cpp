#include "ContainerBaseTest.h"

struct DummyService1 { int _value; virtual ~DummyService1() {} };
struct DummyService2 {};
struct SpecialDummyService : DummyService1, DummyService2 {};

using ResolveRegisteredServiceTypeByTypeTest = ContainerBaseTest;

TEST_F(ResolveRegisteredServiceTypeByTypeTest, ShouldResolveServiceByBaseType_WhenServiceTypeRegisteredAliasedAsBaseType)
{
	builder()
		.registerType<SpecialDummyService>()
		.as<DummyService1>();

	ASSERT_TRUE(std::dynamic_pointer_cast<SpecialDummyService>(container().resolve<std::shared_ptr<DummyService1>>()) != nullptr);
}