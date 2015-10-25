#include <stdafx.h>

#include "ContainerBaseTest.h"

using ServiceFactoryTest = ContainerBaseTest;

namespace
{
	struct DummyService
	{
		int _value;
		explicit DummyService(int value = 0) : _value(value) {}
	};

	struct AbstractDummyService { virtual ~AbstractDummyService() {}; virtual void abstract() = 0; };
	struct ConcreteDummyService : AbstractDummyService { virtual void abstract() override {} };
}

TEST_F(ServiceFactoryTest, ShouldNotCompile_WhenRegisteringServiceAsPtrFactory_AndAutoManaged)
{
//	builder().registerFactory([] { static auto service = DummyService(); return &service; }).autoManaged();
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsCopy_WhenServiceRegisteredAsInstanceFactory)
{
	builder()
		.registerFactory([] { return DummyService(13); });

	ASSERT_EQ(13, container().resolve<DummyService>()._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsCopy_WhenServiceRegisteredAsPtrFactory)
{
	builder()
		.registerFactory([] { static auto service = DummyService(13);  return &service; });

	ASSERT_EQ(13, container().resolve<DummyService>()._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsCopy_WhenServiceRegisteredAsSharedPtrFactory)
{
	builder()
		.registerFactory([] { return std::make_shared<DummyService>(13); });

	ASSERT_EQ(13, container().resolve<DummyService>()._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsCopy_WhenServiceRegisteredAsUniquePtrFactory)
{
	builder()
		.registerFactory([] { return std::make_unique<DummyService>(13); });

	ASSERT_EQ(13, container().resolve<DummyService>()._value);
}

TEST_F(ServiceFactoryTest, ShouldThrowException_WhenResolvingServiceAsRef_AndServiceRegisteredAsInstanceFactory_AndNotAutoManaged)
{
	builder()
		.registerFactory([] { return DummyService(); });

	ASSERT_THROW(container().resolve<DummyService&>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsRef_WhenServiceRegisteredAsInstanceFactory_AndAutoManaged)
{
	builder()
		.registerFactory([] { return DummyService(16); })
		.autoManaged();

	ASSERT_EQ(16, container().resolve<DummyService&>()._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsRef_WhenServiceRegisteredAsPtrFactory)
{
	builder()
		.registerFactory([] { static auto service = DummyService(20);  return &service; });

	ASSERT_EQ(20, container().resolve<DummyService&>()._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveSameServiceInstanceAsRef_WhenServiceRegisteredAsPtrFactory)
{
	auto service = DummyService();

	builder()
		.registerFactory([&service] { return &service; });

	ASSERT_EQ(&service, &container().resolve<DummyService&>());
}

TEST_F(ServiceFactoryTest, ShouldThrowException_WhenResolvingServiceAsRef_AndServiceRegisteredAsSharedPtrFactory_AndNotAutoManaged)
{
	builder()
		.registerFactory([] { return std::make_shared<DummyService>(); });

	ASSERT_THROW(container().resolve<DummyService&>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsRef_WhenServiceRegisteredAsSharedPtrFactory_AndAutoManaged)
{
	builder()
		.registerFactory([] { return std::make_shared<DummyService>(11); })
		.autoManaged();

	ASSERT_EQ(11, container().resolve<DummyService&>()._value);
}

TEST_F(ServiceFactoryTest, ShouldThrowException_WhenResolvingServiceAsRef_AndServiceRegisteredAsUniquePtrFactory_AndNotAutoManaged)
{
	builder()
		.registerFactory([] { return std::make_unique<DummyService>(); });

	ASSERT_THROW(container().resolve<DummyService&>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsRef_WhenServiceRegisteredAsUniquePtrFactory_AndAutoManaged)
{
	builder()
		.registerFactory([] { return std::make_unique<DummyService>(14); })
		.autoManaged();

	ASSERT_EQ(14, container().resolve<DummyService&>()._value);
}

TEST_F(ServiceFactoryTest, ShouldThrowException_WhenResolvingServiceAsPtr_AndServiceRegisteredAsInstanceFactory_AndNotAutoManaged)
{
	builder()
		.registerFactory([] { return DummyService(); });

	ASSERT_THROW(container().resolve<DummyService*>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsPtr_WhenServiceRegisteredAsInstanceFactory_AndAutoManaged)
{
	builder()
		.registerFactory([] { return DummyService(11); })
		.autoManaged();

	ASSERT_EQ(11, container().resolve<DummyService*>()->_value);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsPtr_WhenServiceRegisteredAsPtrFactory)
{
	builder()
		.registerFactory([] { static auto service = DummyService(20);  return &service; });

	ASSERT_EQ(20, container().resolve<DummyService*>()->_value);
}

TEST_F(ServiceFactoryTest, ShouldResolveSameServiceInstanceAsPtr_WhenServiceRegisteredAsPtrFactory)
{
	auto service = DummyService();

	builder()
		.registerFactory([&service] { return &service; });

	ASSERT_EQ(&service, container().resolve<DummyService*>());
}

TEST_F(ServiceFactoryTest, ShouldThrowException_WhenResolvingServiceAsPtr_AndServiceRegisteredAsSharedPtrFactory_AndNotAutoManaged)
{
	builder()
		.registerFactory([] { return std::make_shared<DummyService>(); });

	ASSERT_THROW(container().resolve<DummyService*>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsPtr_WhenServiceRegisteredAsSharedPtrFactory_AndAutoManaged)
{
	builder()
		.registerFactory([] { return std::make_shared<DummyService>(11); })
		.autoManaged();

	ASSERT_EQ(11, container().resolve<DummyService*>()->_value);
}

TEST_F(ServiceFactoryTest, ShouldThrowException_WhenResolvingServiceAsPtr_AndServiceRegisteredAsUniqePtrFactory_AndNotAutoManaged)
{
	builder()
		.registerFactory([] { return std::make_unique<DummyService>(); });

	ASSERT_THROW(container().resolve<DummyService*>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsPtr_WhenServiceRegisteredAsUniqePtrFactory_AndAutoManaged)
{
	builder()
		.registerFactory([] { return std::make_unique<DummyService>(12); })
		.autoManaged();

	ASSERT_EQ(12, container().resolve<DummyService*>()->_value);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsUniquePtr_WhenServiceRegisteredAsInstanceFactory)
{
	builder()
		.registerFactory([] { return DummyService(11); });

	ASSERT_EQ(11, container().resolve<std::unique_ptr<DummyService>>()->_value);
}

TEST_F(ServiceFactoryTest, ShouldThrowException_WhenResolvingServiceAsUniquePtr_AndServiceRegisteredAsPtrFactory)
{
	builder()
		.registerFactory([] { static auto service = DummyService();  return &service; });

	ASSERT_THROW(container().resolve<std::unique_ptr<DummyService>>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceFactoryTest, ShouldThrowException_WhenResolvingServiceAsUniquePtr_AndServiceRegisteredAsSharedPtrFactory)
{
	builder()
		.registerFactory([] { return std::make_shared<DummyService>(); });

	ASSERT_THROW(container().resolve<std::unique_ptr<DummyService>>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsUniquePtr_WhenServiceRegisteredAsUniquePtrFactory)
{
	builder()
		.registerFactory([] { return std::make_unique<DummyService>(12); });

	ASSERT_EQ(12, container().resolve<std::unique_ptr<DummyService>>()->_value);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsSharedPtr_WhenServiceRegisteredAsInstanceFactory)
{
	builder()
		.registerFactory([] { return DummyService(15); });

	ASSERT_EQ(15, container().resolve<std::shared_ptr<DummyService>>()->_value);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsSharedPtr_WhenServiceRegisteredAsPtrFactory)
{
	builder()
		.registerFactory([] { static auto service = DummyService(16);  return &service; });

	ASSERT_EQ(16, container().resolve<std::shared_ptr<DummyService>>()->_value);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsSharedPtr_WhenServiceRegisteredAsSharedPtrFactory)
{
	builder()
		.registerFactory([] { return std::make_shared<DummyService>(17); });

	ASSERT_EQ(17, container().resolve<std::shared_ptr<DummyService>>()->_value);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsSharedPtr_WhenServiceRegisteredAsUniquePtrFactory)
{
	builder()
		.registerFactory([] { return std::make_unique<DummyService>(18); });

	ASSERT_EQ(18, container().resolve<std::shared_ptr<DummyService>>()->_value);
}

TEST_F(ServiceFactoryTest, ShouldResolveService_WhenServiceRegisteredAsInstanceFactoryFunction)
{
	std::function<DummyService()> factory = [] { return DummyService(14); };

	builder()
		.registerFactory(factory);

	ASSERT_EQ(14, container().resolve<DummyService>()._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveService_WhenServiceRegisteredAsPtrFactoryFunction)
{
	std::function<DummyService*()> factory = [] { static auto service = DummyService(14); return &service; };

	builder()
		.registerFactory(factory);

	ASSERT_EQ(14, container().resolve<DummyService>()._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveService_WhenServiceRegisteredAsSharedPtrFactoryFunction)
{
	std::function<std::shared_ptr<DummyService>()> factory = [] { return std::make_shared<DummyService>(14); };

	builder()
		.registerFactory(factory);

	ASSERT_EQ(14, container().resolve<DummyService>()._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveService_WhenServiceRegisteredAsUniquePtrFactoryFunction)
{
	std::function<std::unique_ptr<DummyService>()> factory = [] { return std::make_unique<DummyService>(14); };

	builder()
		.registerFactory(factory);

	ASSERT_EQ(14, container().resolve<DummyService>()._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveService_WhenServiceRegisteredAsInstanceFactoryLambdaWithCapture)
{
	auto service = DummyService(14);

	builder()
		.registerFactory([service] { return service; });

	ASSERT_EQ(14, container().resolve<DummyService>()._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveService_WhenServiceRegisteredAsPtrFactoryLambdaWithCapture)
{
	auto service = DummyService(14);

	builder()
		.registerFactory([&service] { return &service; });

	ASSERT_EQ(14, container().resolve<DummyService>()._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveService_WhenServiceRegisteredAsSharedPtrFactoryLambdaWithCapture)
{
	auto service = std::make_shared<DummyService>(14);

	builder()
		.registerFactory([service] { return service; });

	ASSERT_EQ(14, container().resolve<DummyService>()._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveService_WhenServiceRegisteredAsUniquePtrFactoryLambdaWithCapture)
{
	auto service = std::make_unique<DummyService>(14);

	builder()
		.registerFactory([&service] { return std::move(service); });

	ASSERT_EQ(14, container().resolve<DummyService>()._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsSPtr_WhenServiceRegisteredAsFactoryReturningSharedPtrOfAbstractBaseType)
{
	builder()
		.registerFactory([] { return std::shared_ptr<AbstractDummyService>(std::make_shared<ConcreteDummyService>()); })
		.autoManaged();

	ASSERT_TRUE(dynamic_cast<ConcreteDummyService*>(container().resolve<std::shared_ptr<AbstractDummyService>>().get()) != nullptr);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsSPtr_WhenServiceRegisteredAsFactoryReturningPtrOfAbstractBaseType)
{
	builder()
		.registerFactory([] { static auto service = ConcreteDummyService(); return static_cast<AbstractDummyService*>(&service); });

	ASSERT_TRUE(dynamic_cast<ConcreteDummyService*>(container().resolve<AbstractDummyService*>()) != nullptr);
}
