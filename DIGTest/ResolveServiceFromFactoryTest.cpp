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

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveServiceBySharedPtr_WhenServiceRegisteredAsSharedPtrFactoryFunction)
{
	std::function<std::shared_ptr<DummyService>()> factory = [] { return std::make_shared<DummyService>(); };

	builder()
		.registerFactory(factory);

	ASSERT_TRUE(std::dynamic_pointer_cast<DummyService>(container().resolve<std::shared_ptr<DummyService>>()) != nullptr);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveServiceBySharedPtr_WhenServiceRegisteredAsSharedPtrFactoryLambdaWithCapture)
{
	auto service = std::make_shared<DummyService>();

	builder()
		.registerFactory([service] { return service; });

	ASSERT_TRUE(std::dynamic_pointer_cast<DummyService>(container().resolve<std::shared_ptr<DummyService>>()) != nullptr);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveServiceBySharedPtr_WhenServiceRegisteredAsPtrFactory)
{
	builder()
		.registerFactory([] { static DummyService service;  return &service; });

	ASSERT_TRUE(std::dynamic_pointer_cast<DummyService>(container().resolve<std::shared_ptr<DummyService>>()) != nullptr);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveServiceBySharedPtr_WhenServiceRegisteredAsPtrFactoryFunction)
{
	std::function<DummyService*()> factory = [] { static DummyService service; return &service; };

	builder()
		.registerFactory(factory);

	ASSERT_TRUE(std::dynamic_pointer_cast<DummyService>(container().resolve<std::shared_ptr<DummyService>>()) != nullptr);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveServiceBySharedPtr_WhenServiceRegisteredAsPtrFactoryLambdaWithCapture)
{
	auto service = std::make_shared<DummyService>();
	auto service_ptr = service.get();

	builder()
		.registerFactory([service_ptr] { return service_ptr; });

	ASSERT_TRUE(std::dynamic_pointer_cast<DummyService>(container().resolve<std::shared_ptr<DummyService>>()) != nullptr);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveServiceBySharedPtr_WhenServiceRegisteredAsUniquePtrFactory)
{
	builder()
		.registerFactory([] { return std::make_unique<DummyService>(); });

	ASSERT_TRUE(std::dynamic_pointer_cast<DummyService>(container().resolve<std::shared_ptr<DummyService>>()) != nullptr);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveServiceBySharedPtr_WhenServiceRegisteredAsUniquePtrFactoryFunction)
{
	std::function<std::unique_ptr<DummyService>()> factory = [] { return std::make_unique<DummyService>(); };

	builder()
		.registerFactory(factory);

	ASSERT_TRUE(std::dynamic_pointer_cast<DummyService>(container().resolve<std::shared_ptr<DummyService>>()) != nullptr);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveServiceBySharedPtr_WhenServiceRegisteredAsUniquePtrFactoryLambdaWithCapture)
{
	auto service = std::make_unique<DummyService>();

	builder()
		.registerFactory([&service] { return std::move(service); });

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

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveServiceBySharedPtr_WhenServiceRegisteredAsInstanceFactoryLambdaWithCapture)
{
	auto service = DummyService();

	builder()
		.registerFactory([service] { return service; });

	ASSERT_TRUE(std::dynamic_pointer_cast<DummyService>(container().resolve<std::shared_ptr<DummyService>>()) != nullptr);
}
