#include <stdafx.h>
#include "ContainerBaseTest.h"

using ServiceOverwriteTest = ContainerBaseTest;

namespace
{
	struct Base { virtual ~Base() {} };
	struct DerivedA : Base {};
	struct DerivedB : Base {};
}

TEST_F(ServiceOverwriteTest, ShouldResolveLatestType_WhenAliasDefinitionOverwritten)
{
	builder().registerType<DerivedA>().as<Base>();
	builder().registerType<DerivedB>().as<Base>();

	auto resolved = container().resolve<std::shared_ptr<Base>>();

	ASSERT_TRUE(dynamic_cast<DerivedB*>(resolved.get()) != nullptr);
}

TEST_F(ServiceOverwriteTest, ShouldResolveWithLatestOptions_WhenDefinitionOverwritten)
{
	builder().registerType<Base>();
	builder().registerType<Base>().singleInstance();

	auto resolved1 = container().resolve<Base*>();
	auto resolved2 = container().resolve<Base*>();

	ASSERT_EQ(resolved1, resolved2);
}