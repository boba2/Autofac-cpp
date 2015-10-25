#include <stdafx.h>
#include "ContainerBaseTest.h"

using ConstServiceTest = ContainerBaseTest;

namespace
{
	struct ServiceA
	{
		std::string method() { return "non-const method"; }
		std::string method() const { return "const method"; }
	};
}

TEST_F(ConstServiceTest, ShouldResolveNonConstObjectRef_WhenNonConstRequested)
{
	builder()
		.registerType<ServiceA>()
		.autoManaged();

	auto& serviceA = container().resolve<ServiceA&>();

	ASSERT_EQ("non-const method", serviceA.method());
}

TEST_F(ConstServiceTest, ShouldResolveConstObjectRef_WhenConstRequested)
{
	builder()
		.registerType<ServiceA>()
		.autoManaged();

	auto& serviceA = container().resolve<const ServiceA&>();

	ASSERT_EQ("const method", serviceA.method());
}

TEST_F(ConstServiceTest, ShouldResolveNonConstObjectPtr_WhenNonConstRequested)
{
	builder()
		.registerType<ServiceA>()
		.autoManaged();

	auto serviceA = container().resolve<ServiceA*>();

	ASSERT_EQ("non-const method", serviceA->method());
}

TEST_F(ConstServiceTest, ShouldResolveConstObjectPtr_WhenConstRequested)
{
	builder()
		.registerType<ServiceA>()
		.autoManaged();

	auto serviceA = container().resolve<const ServiceA*>();

	ASSERT_EQ("const method", serviceA->method());
}

TEST_F(ConstServiceTest, ShouldResolveNonConstObjectSharedPtr_WhenNonConstRequested)
{
	builder()
		.registerType<ServiceA>();

	auto serviceA = container().resolve<std::shared_ptr<ServiceA>>();

	ASSERT_EQ("non-const method", serviceA->method());
}

TEST_F(ConstServiceTest, ShouldResolveConstObjectSharedPtr_WhenConstRequested)
{
	builder()
		.registerType<ServiceA>();

	auto serviceA = container().resolve<std::shared_ptr<const ServiceA>>();

	ASSERT_EQ("const method", serviceA->method());
}

TEST_F(ConstServiceTest, ShouldResolveNonConstObjectUniquePtr_WhenNonConstRequested)
{
	builder()
		.registerType<ServiceA>();

	auto serviceA = container().resolve<std::unique_ptr<ServiceA>>();

	ASSERT_EQ("non-const method", serviceA->method());
}

TEST_F(ConstServiceTest, ShouldResolveConstObjectUniquePtr_WhenConstRequested)
{
	builder()
		.registerType<ServiceA>();

	auto serviceA = container().resolve<std::unique_ptr<const ServiceA>>();

	ASSERT_EQ("const method", serviceA->method());
}

TEST_F(ConstServiceTest, ShouldResolveObjectThroughCopy_WhenConstRequested)
{
	builder()
		.registerType<ServiceA>()
		.autoManaged();

	auto serviceA = container().resolve<const ServiceA>();

	ASSERT_EQ("non-const method", serviceA.method());
}
