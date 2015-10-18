#include "ContainerBaseTest.h"

struct DummyService {};
struct SpecialDummyService : DummyService {};

TEST_F(ContainerBaseTest, ShouldResolveServiceByPointer_WhenServiceTypeRegistered)
{
	builder().registerType<DummyService>();

	ASSERT_TRUE(dynamic_cast<DummyService *>(container().resolve<DummyService *>()) != nullptr);
}

TEST_F(ContainerBaseTest, ShouldResolveServiceByCopy_WhenServiceTypeRegistered)
{
	builder().registerType<DummyService>();

	auto service = container().resolve<DummyService>();
}

TEST_F(ContainerBaseTest, ShouldResolveServiceBySharedPtr_WhenServiceTypeRegistered)
{
	builder().registerType<DummyService>();

	ASSERT_TRUE(dynamic_cast<DummyService *>(container().resolve<std::shared_ptr<DummyService>>().get()) != nullptr);
}