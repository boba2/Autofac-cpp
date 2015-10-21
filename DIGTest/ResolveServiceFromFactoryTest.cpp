#include "ContainerBaseTest.h"

using ResolveServiceFromFactoryTest = ContainerBaseTest;

namespace
{
	struct DummyService {};
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveServiceBySharedPtr_WhenServiceRegisteredAsSharedPtrFactory)
{
	builder()
		.registerFactory([] { return std::make_shared<DummyService>(); });

	ASSERT_TRUE(std::dynamic_pointer_cast<DummyService>(container().resolve<std::shared_ptr<DummyService>>()) != nullptr);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveServiceBySharedPtr_WhenServiceRegisteredAsPtrFactory)
{
	builder()
		.registerFactory([] { return new DummyService; });

	ASSERT_TRUE(std::dynamic_pointer_cast<DummyService>(container().resolve<std::shared_ptr<DummyService>>()) != nullptr);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveServiceBySharedPtr_WhenServiceRegisteredAsUniquePtrFactory)
{
	builder()
		.registerFactory([] { return std::make_unique<DummyService>(); });

	ASSERT_TRUE(std::dynamic_pointer_cast<DummyService>(container().resolve<std::shared_ptr<DummyService>>()) != nullptr);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveServiceBySharedPtr_WhenServiceRegisteredAsInstanceFactory)
{
	builder()
		.registerFactory([] { return DummyService(); });

	ASSERT_TRUE(std::dynamic_pointer_cast<DummyService>(container().resolve<std::shared_ptr<DummyService>>()) != nullptr);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveServiceBySharedPtr_WhenServiceRegisteredAsInstanceFactoryFunction)
{
	std::function<DummyService()> factory = [] { return DummyService(); };

	builder()
		.registerFactory(factory);

	ASSERT_TRUE(std::dynamic_pointer_cast<DummyService>(container().resolve<std::shared_ptr<DummyService>>()) != nullptr);
}
