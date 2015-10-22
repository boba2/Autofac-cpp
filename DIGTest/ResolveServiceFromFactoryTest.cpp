#include "ContainerBaseTest.h"

using ResolveServiceFromFactoryTest = ContainerBaseTest;

namespace
{
	struct DummyService
	{
		int _value;
		DummyService(int value = 0) : _value(value) {}
	};

	struct AbstractDummyService { virtual ~AbstractDummyService() {}; virtual void abstract() = 0; };
	struct ConcreteDummyService : AbstractDummyService { virtual void abstract() override {} };
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveServiceByCopy_WhenServiceRegisteredAsInstanceFactory)
{
	builder()
		.registerFactory([] { return DummyService(13); });

	ASSERT_EQ(13, container().resolve<DummyService>()._value);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveServiceByCopy_WhenServiceRegisteredAsPtrFactory)
{
	builder()
		.registerFactory([] { static DummyService service(13);  return &service; });

	ASSERT_EQ(13, container().resolve<DummyService>()._value);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveServiceByCopy_WhenServiceRegisteredAsSharedPtrFactory)
{
	builder()
		.registerFactory([] { return std::make_shared<DummyService>(13); });

	ASSERT_EQ(13, container().resolve<DummyService>()._value);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveServiceByCopy_WhenServiceRegisteredAsUniquePtrFactory)
{
	builder()
		.registerFactory([] { return std::make_unique<DummyService>(13); });

	ASSERT_EQ(13, container().resolve<DummyService>()._value);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveServiceBySharedPtr_WhenServiceRegisteredAsInstanceFactory)
{
	builder()
		.registerFactory([] { return DummyService(); });

	ASSERT_TRUE(std::dynamic_pointer_cast<DummyService>(container().resolve<std::shared_ptr<DummyService>>()) != nullptr);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveServiceBySharedPtr_WhenServiceRegisteredAsPtrFactory)
{
	builder()
		.registerFactory([] { static DummyService service;  return &service; });

	ASSERT_TRUE(std::dynamic_pointer_cast<DummyService>(container().resolve<std::shared_ptr<DummyService>>()) != nullptr);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveServiceBySharedPtr_WhenServiceRegisteredAsSharedPtrFactory)
{
	builder()
		.registerFactory([] { return std::make_shared<DummyService>(); });

	ASSERT_TRUE(std::dynamic_pointer_cast<DummyService>(container().resolve<std::shared_ptr<DummyService>>()) != nullptr);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveServiceBySharedPtr_WhenServiceRegisteredAsUniquePtrFactory)
{
	builder()
		.registerFactory([] { return std::make_unique<DummyService>(); });

	ASSERT_TRUE(std::dynamic_pointer_cast<DummyService>(container().resolve<std::shared_ptr<DummyService>>()) != nullptr);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveService_WhenServiceRegisteredAsInstanceFactoryFunction)
{
	std::function<DummyService()> factory = [] { return DummyService(14); };

	builder()
		.registerFactory(factory);

	ASSERT_EQ(14, container().resolve<DummyService>()._value);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveService_WhenServiceRegisteredAsPtrFactoryFunction)
{
	std::function<DummyService*()> factory = [] { static DummyService service(14); return &service; };

	builder()
		.registerFactory(factory);

	ASSERT_EQ(14, container().resolve<DummyService>()._value);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveService_WhenServiceRegisteredAsSharedPtrFactoryFunction)
{
	std::function<std::shared_ptr<DummyService>()> factory = [] { return std::make_shared<DummyService>(14); };

	builder()
		.registerFactory(factory);

	ASSERT_EQ(14, container().resolve<DummyService>()._value);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveService_WhenServiceRegisteredAsUniquePtrFactoryFunction)
{
	std::function<std::unique_ptr<DummyService>()> factory = [] { return std::make_unique<DummyService>(14); };

	builder()
		.registerFactory(factory);

	ASSERT_EQ(14, container().resolve<DummyService>()._value);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveService_WhenServiceRegisteredAsInstanceFactoryLambdaWithCapture)
{
	auto service = DummyService(14);

	builder()
		.registerFactory([service] { return service; });

	ASSERT_EQ(14, container().resolve<DummyService>()._value);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveService_WhenServiceRegisteredAsPtrFactoryLambdaWithCapture)
{
	auto service = DummyService(14);

	builder()
		.registerFactory([&service] { return &service; });

	ASSERT_EQ(14, container().resolve<DummyService>()._value);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveService_WhenServiceRegisteredAsSharedPtrFactoryLambdaWithCapture)
{
	auto service = std::make_shared<DummyService>(14);

	builder()
		.registerFactory([service] { return service; });

	ASSERT_EQ(14, container().resolve<DummyService>()._value);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveService_WhenServiceRegisteredAsUniquePtrFactoryLambdaWithCapture)
{
	auto service = std::make_unique<DummyService>(14);

	builder()
		.registerFactory([&service] { return std::move(service); });

	ASSERT_EQ(14, container().resolve<DummyService>()._value);
}

TEST_F(ResolveServiceFromFactoryTest, ShouldResolveServiceAsSharedPtr_WhenServiceRegisteredAsFactoryReturningAbstractBaseType)
{
	builder()
		.registerFactory([] { return std::shared_ptr<AbstractDummyService>(std::make_shared<ConcreteDummyService>()); });

	ASSERT_TRUE(std::dynamic_pointer_cast<ConcreteDummyService>(container().resolve<std::shared_ptr<AbstractDummyService>>()) != nullptr);
}
