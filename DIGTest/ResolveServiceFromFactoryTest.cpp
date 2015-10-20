#include "ContainerBaseTest.h"

using ResolveServiceFromFactoryTest = ContainerBaseTest;

namespace
{
	struct DummyService {};
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveServiceBySharedPtr_WhenServiceAsSharedPtrFactoryRegistered)
{
	builder()
		.registerFactory([] { return std::make_shared<DummyService>(); });

	ASSERT_TRUE(std::dynamic_pointer_cast<DummyService>(container().resolve<std::shared_ptr<DummyService>>()) != nullptr);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveServiceBySharedPtr_WhenServiceAsPtrFactoryRegistered)
{
	builder()
		.registerFactory([] { return new DummyService; });

	ASSERT_TRUE(std::dynamic_pointer_cast<DummyService>(container().resolve<std::shared_ptr<DummyService>>()) != nullptr);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveServiceBySharedPtr_WhenServiceAsUniquePtrFactoryRegistered)
{
	builder()
		.registerFactory([] { return std::make_unique<DummyService>(); });

	ASSERT_TRUE(std::dynamic_pointer_cast<DummyService>(container().resolve<std::shared_ptr<DummyService>>()) != nullptr);
}
