#include "ContainerBaseTest.h"

struct DummyService1 { virtual ~DummyService1() {} };
struct SpecialDummyService : DummyService1 {};

using ResolveServiceTypeAsSingleInstance = ContainerBaseTest;

TEST_F(ResolveServiceTypeAsSingleInstance, ShouldResolveSingleServiceByBaseType_WhenServiceTypeRegisteredAliasedAsBaseType_AndAsSingleInstance)
{
	builder()
		.registerType<SpecialDummyService>()
		.as<DummyService1>()
		.singleInstance();

	auto service1 = container().resolve<std::shared_ptr<DummyService1>>();
	auto service2 = container().resolve<std::shared_ptr<DummyService1>>();

	ASSERT_EQ(service1, service2);
}