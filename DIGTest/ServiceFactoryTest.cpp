#include <stdafx.h>

#include "ContainerBaseTest.h"

using ServiceFactoryTest = ContainerBaseTest;

namespace
{
	struct Service
	{
		int _value;
		explicit Service(int value = 0) : _value(value) {}
	};

	struct AbstractService { virtual ~AbstractService() {}; virtual void abstract() = 0; };
	struct ConcreteService : AbstractService { virtual void abstract() override {} };
}

TEST_F(ServiceFactoryTest, ShouldThrowException_WhenRegisteringServiceAsPtrFactory_AndAutoManaged)
{
	ASSERT_THROW(builder().registerFactory([] { static auto service = Service(); return &service; }).autoManaged(), std::logic_error);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsCopy_WhenServiceRegisteredAsInstanceFactory)
{
	builder()
		.registerFactory([] { return Service(13); });

	auto resolved = container().resolve<Service>();

	ASSERT_EQ(13, resolved._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsCopy_WhenServiceRegisteredAsPtrFactory)
{
	builder()
		.registerFactory([] { static auto service = Service(13);  return &service; });

	auto resolved = container().resolve<Service>();

	ASSERT_EQ(13, resolved._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsCopy_WhenServiceRegisteredAsSharedPtrFactory)
{
	builder()
		.registerFactory([] { return std::make_shared<Service>(13); });

	auto resolved = container().resolve<Service>();

	ASSERT_EQ(13, resolved._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsCopy_WhenServiceRegisteredAsUniquePtrFactory)
{
	builder()
		.registerFactory([] { return std::make_unique<Service>(13); });

	auto resolved = container().resolve<Service>();

	ASSERT_EQ(13, resolved._value);
}

TEST_F(ServiceFactoryTest, ShouldThrowException_WhenResolvingServiceAsRef_AndServiceRegisteredAsInstanceFactory_AndNotAutoManaged)
{
	builder()
		.registerFactory([] { return Service(); });

	ASSERT_THROW(container().resolve<Service&>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsRef_WhenServiceRegisteredAsInstanceFactory_AndAutoManaged)
{
	builder()
		.registerFactory([] { return Service(16); })
		.autoManaged();

	auto& resolved = container().resolve<Service&>();

	ASSERT_EQ(16, resolved._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveServicesAsDistinctRefs_WhenServiceRegisteredAsInstanceFactory_AndAutoManaged)
{
	builder()
		.registerFactory([] { return Service(); })
		.autoManaged();

	auto& resolved1 = container().resolve<Service&>();
	auto& resolved2 = container().resolve<Service&>();

	ASSERT_NE(&resolved1, &resolved2);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsRef_WhenServiceRegisteredAsPtrFactory)
{
	builder()
		.registerFactory([] { static auto service = Service(20);  return &service; });

	auto& resolved = container().resolve<Service&>();

	ASSERT_EQ(20, resolved._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveSameServiceInstanceAsRef_WhenServiceRegisteredAsPtrFactory)
{
	auto service = Service();

	builder()
		.registerFactory([&service] { return &service; });

	auto& resolved = container().resolve<Service&>();

	ASSERT_EQ(&service, &resolved);
}

TEST_F(ServiceFactoryTest, ShouldThrowException_WhenResolvingServiceAsRef_AndServiceRegisteredAsSharedPtrFactory_AndNotAutoManaged)
{
	builder()
		.registerFactory([] { return std::make_shared<Service>(); });

	ASSERT_THROW(container().resolve<Service&>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsRef_WhenServiceRegisteredAsSharedPtrFactory_AndAutoManaged)
{
	builder()
		.registerFactory([] { return std::make_shared<Service>(11); })
		.autoManaged();

	auto& resolved = container().resolve<Service&>();

	ASSERT_EQ(11, resolved._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveServicesAsDistinctRefs_WhenServiceRegisteredAsSharedPtrFactory_AndAutoManaged)
{
	builder()
		.registerFactory([] { return std::make_shared<Service>(); })
		.autoManaged();

	auto& resolved1 = container().resolve<Service&>();
	auto& resolved2 = container().resolve<Service&>();

	ASSERT_NE(&resolved1, &resolved2);
}

TEST_F(ServiceFactoryTest, ShouldThrowException_WhenResolvingServiceAsRef_AndServiceRegisteredAsUniquePtrFactory_AndNotAutoManaged)
{
	builder()
		.registerFactory([] { return std::make_unique<Service>(); });

	ASSERT_THROW(container().resolve<Service&>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsRef_WhenServiceRegisteredAsUniquePtrFactory_AndAutoManaged)
{
	builder()
		.registerFactory([] { return std::make_unique<Service>(14); })
		.autoManaged();

	auto& resolved = container().resolve<Service&>();

	ASSERT_EQ(14, resolved._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveServicesAsDistinctRefs_WhenServiceRegisteredAsUniquePtrFactory_AndAutoManaged)
{
	builder()
		.registerFactory([] { return std::make_unique<Service>(); })
		.autoManaged();

	auto& resolved1 = container().resolve<Service&>();
	auto& resolved2 = container().resolve<Service&>();

	ASSERT_NE(&resolved1, &resolved2);
}

TEST_F(ServiceFactoryTest, ShouldThrowException_WhenResolvingServiceAsPtr_AndServiceRegisteredAsInstanceFactory_AndNotAutoManaged)
{
	builder()
		.registerFactory([] { return Service(); });

	ASSERT_THROW(container().resolve<Service*>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsPtr_WhenServiceRegisteredAsInstanceFactory_AndAutoManaged)
{
	builder()
		.registerFactory([] { return Service(11); })
		.autoManaged();

	auto resolved = container().resolve<Service*>();

	ASSERT_EQ(11, resolved->_value);
}

TEST_F(ServiceFactoryTest, ShouldResolveServicesAsDistinctPtrs_WhenServiceRegisteredAsInstanceFactory_AndAutoManaged)
{
	builder()
		.registerFactory([] { return Service(); })
		.autoManaged();

	auto resolved1 = container().resolve<Service*>();
	auto resolved2 = container().resolve<Service*>();

	ASSERT_NE(resolved1, resolved2);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsPtr_WhenServiceRegisteredAsPtrFactory)
{
	builder()
		.registerFactory([] { static auto service = Service(20);  return &service; });

	auto resolved = container().resolve<Service*>();

	ASSERT_EQ(20, resolved->_value);
}

TEST_F(ServiceFactoryTest, ShouldResolveSameServiceInstanceAsPtr_WhenServiceRegisteredAsPtrFactory)
{
	auto service = Service();

	builder()
		.registerFactory([&service] { return &service; });

	auto resolved = container().resolve<Service*>();

	ASSERT_EQ(&service, resolved);
}

TEST_F(ServiceFactoryTest, ShouldThrowException_WhenResolvingServiceAsPtr_AndServiceRegisteredAsSharedPtrFactory_AndNotAutoManaged)
{
	builder()
		.registerFactory([] { return std::make_shared<Service>(); });

	ASSERT_THROW(container().resolve<Service*>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsPtr_WhenServiceRegisteredAsSharedPtrFactory_AndAutoManaged)
{
	builder()
		.registerFactory([] { return std::make_shared<Service>(11); })
		.autoManaged();

	auto resolved = container().resolve<Service*>();

	ASSERT_EQ(11, resolved->_value);
}

TEST_F(ServiceFactoryTest, ShouldResolveServicesAsDistinctPtrs_WhenServiceRegisteredAsSharedPtrFactory_AndAutoManaged)
{
	builder()
		.registerFactory([] { return std::make_shared<Service>(); })
		.autoManaged();

	auto resolved1 = container().resolve<Service*>();
	auto resolved2 = container().resolve<Service*>();

	ASSERT_NE(resolved1, resolved2);
}

TEST_F(ServiceFactoryTest, ShouldThrowException_WhenResolvingServiceAsPtr_AndServiceRegisteredAsUniqePtrFactory_AndNotAutoManaged)
{
	builder()
		.registerFactory([] { return std::make_unique<Service>(); });

	ASSERT_THROW(container().resolve<Service*>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsPtr_WhenServiceRegisteredAsUniqePtrFactory_AndAutoManaged)
{
	builder()
		.registerFactory([] { return std::make_unique<Service>(12); })
		.autoManaged();

	auto resolved = container().resolve<Service*>();

	ASSERT_EQ(12, resolved->_value);
}

TEST_F(ServiceFactoryTest, ShouldResolveServicesAsDistinctPtrs_WhenServiceRegisteredAsUniqePtrFactory_AndAutoManaged)
{
	builder()
		.registerFactory([] { return std::make_unique<Service>(); })
		.autoManaged();

	auto resolved1 = container().resolve<Service*>();
	auto resolved2 = container().resolve<Service*>();

	ASSERT_NE(resolved1, resolved2);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsUniquePtr_WhenServiceRegisteredAsInstanceFactory)
{
	builder()
		.registerFactory([] { return Service(11); });

	auto resolved = container().resolve<std::unique_ptr<Service>>();

	ASSERT_EQ(11, resolved->_value);
}

TEST_F(ServiceFactoryTest, ShouldThrowException_WhenResolvingServiceAsUniquePtr_AndServiceRegisteredAsPtrFactory)
{
	builder()
		.registerFactory([] { static auto service = Service();  return &service; });

	ASSERT_THROW(container().resolve<std::unique_ptr<Service>>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceFactoryTest, ShouldThrowException_WhenResolvingServiceAsUniquePtr_AndServiceRegisteredAsSharedPtrFactory)
{
	builder()
		.registerFactory([] { return std::make_shared<Service>(); });

	ASSERT_THROW(container().resolve<std::unique_ptr<Service>>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsUniquePtr_WhenServiceRegisteredAsUniquePtrFactory)
{
	builder()
		.registerFactory([] { return std::make_unique<Service>(12); });

	auto resolved = container().resolve<std::unique_ptr<Service>>();

	ASSERT_EQ(12, resolved->_value);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsSharedPtr_WhenServiceRegisteredAsInstanceFactory)
{
	builder()
		.registerFactory([] { return Service(15); });

	auto resolved = container().resolve<std::shared_ptr<Service>>();

	ASSERT_EQ(15, resolved->_value);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsSharedPtr_WhenServiceRegisteredAsPtrFactory)
{
	builder()
		.registerFactory([] { static auto service = Service(16);  return &service; });

	auto resolved = container().resolve<std::shared_ptr<Service>>();

	ASSERT_EQ(16, resolved->_value);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsSharedPtr_WhenServiceRegisteredAsSharedPtrFactory)
{
	builder()
		.registerFactory([] { return std::make_shared<Service>(17); });

	auto resolved = container().resolve<std::shared_ptr<Service>>();

	ASSERT_EQ(17, resolved->_value);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsSharedPtr_WhenServiceRegisteredAsUniquePtrFactory)
{
	builder()
		.registerFactory([] { return std::make_unique<Service>(18); });

	auto resolved = container().resolve<std::shared_ptr<Service>>();

	ASSERT_EQ(18, resolved->_value);
}

TEST_F(ServiceFactoryTest, ShouldResolveService_WhenServiceRegisteredAsInstanceFactoryFunction)
{
	std::function<Service()> factory = [] { return Service(14); };

	builder()
		.registerFactory(factory);

	auto resolved = container().resolve<Service>();

	ASSERT_EQ(14, resolved._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveService_WhenServiceRegisteredAsPtrFactoryFunction)
{
	std::function<Service*()> factory = [] { static auto service = Service(14); return &service; };

	builder()
		.registerFactory(factory);

	auto resolved = container().resolve<Service>();

	ASSERT_EQ(14, resolved._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveService_WhenServiceRegisteredAsSharedPtrFactoryFunction)
{
	std::function<std::shared_ptr<Service>()> factory = [] { return std::make_shared<Service>(14); };

	builder()
		.registerFactory(factory);

	auto resolved = container().resolve<Service>();

	ASSERT_EQ(14, resolved._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveService_WhenServiceRegisteredAsUniquePtrFactoryFunction)
{
	std::function<std::unique_ptr<Service>()> factory = [] { return std::make_unique<Service>(14); };

	builder()
		.registerFactory(factory);

	auto resolved = container().resolve<Service>();

	ASSERT_EQ(14, resolved._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveService_WhenServiceRegisteredAsInstanceFactoryLambdaWithCapture)
{
	auto service = Service(14);

	builder()
		.registerFactory([service] { return service; });

	auto resolved = container().resolve<Service>();

	ASSERT_EQ(14, resolved._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveService_WhenServiceRegisteredAsPtrFactoryLambdaWithCapture)
{
	auto service = Service(14);

	builder()
		.registerFactory([&service] { return &service; });

	auto resolved = container().resolve<Service>();

	ASSERT_EQ(14, resolved._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveService_WhenServiceRegisteredAsSharedPtrFactoryLambdaWithCapture)
{
	auto service = std::make_shared<Service>(14);

	builder()
		.registerFactory([service] { return service; });

	auto resolved = container().resolve<Service>();

	ASSERT_EQ(14, resolved._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveService_WhenServiceRegisteredAsUniquePtrFactoryLambdaWithCapture)
{
	auto service = std::make_unique<Service>(14);

	builder()
		.registerFactory([&service] { return std::move(service); });

	auto resolved = container().resolve<Service>();

	ASSERT_EQ(14, resolved._value);
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsSPtr_WhenServiceRegisteredAsFactoryReturningSharedPtrOfAbstractBaseType)
{
	builder()
		.registerFactory([] { return std::shared_ptr<AbstractService>(std::make_shared<ConcreteService>()); })
		.autoManaged();

	auto resolved = container().resolve<std::shared_ptr<AbstractService>>();

	ASSERT_TRUE(isOfType<ConcreteService>(resolved.get()));
}

TEST_F(ServiceFactoryTest, ShouldResolveServiceAsSPtr_WhenServiceRegisteredAsFactoryReturningPtrOfAbstractBaseType)
{
	builder()
		.registerFactory([] { static auto service = ConcreteService(); return static_cast<AbstractService*>(&service); });

	auto resolved = container().resolve<AbstractService*>();

	ASSERT_TRUE(isOfType<ConcreteService>(resolved));
}
