#include <stdafx.h>
#include "ContainerBaseTest.h"

using ServiceOverwriteTest = ContainerBaseTest;

namespace
{
	struct Base { virtual ~Base() {} };
	struct Derived1 : Base {};
	struct Derived2 : Base {};
}

TEST_F(ServiceOverwriteTest, ShouldResolveLatestType_WhenAliasDefinitionOverwritten)
{
	builder().registerType<Derived1>().as<Base>();
	builder().registerType<Derived2>().as<Base>();

	auto service = container().resolve<std::shared_ptr<Base>>();

	ASSERT_TRUE(dynamic_cast<Derived2*>(service.get()) != nullptr);
}

TEST_F(ServiceOverwriteTest, ShouldResolveWithLatestOptions_WhenDefinitionOverwritten)
{
	builder().registerType<Base>();
	builder().registerType<Base>().singleInstance();

	auto service1 = container().resolve<Base*>();
	auto service2 = container().resolve<Base*>();

	ASSERT_EQ(service1, service2);
}