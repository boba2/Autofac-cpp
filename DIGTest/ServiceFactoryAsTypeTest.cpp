#include <stdafx.h>
#include "ContainerBaseTest.h"
#include "../DI/Error/ServiceNotRegistered.h"

using ServiceFactoryAsType = ContainerBaseTest;

namespace
{
	struct ServiceA { virtual ~ServiceA() {} };
	struct ServiceB {};
	struct SpecialService : ServiceA {};

	struct AbstractService { virtual ~AbstractService() {}; virtual void abstract() = 0; };
	struct ConcreteService : AbstractService { virtual void abstract() override {} };
}

TEST_F(ServiceFactoryAsType, ShouldResolveServiceAsBaseTypeAsPtr_WhenServiceFactoryRegisteredAliasedAsBaseType)
{
	builder()
		.registerFactory([] { return SpecialService(); })
		.as<ServiceA>()
		.autoManaged();

	auto service = container().resolve<ServiceA*>();

	ASSERT_TRUE(isOfType<SpecialService>(service));
}

TEST_F(ServiceFactoryAsType, ShouldResolveServiceAsBaseTypeAsPtr_WhenServiceFactoryRegisteredAliasedAsAbstractBaseType)
{
	builder()
		.registerFactory([] { return ConcreteService(); })
		.as<AbstractService>()
		.autoManaged();

	auto service = container().resolve<AbstractService*>();

	ASSERT_TRUE(isOfType<ConcreteService>(service));
}

TEST_F(ServiceFactoryAsType, ShouldResolveServiceAsBaseTypeAsConstRef_WhenServiceFactoryRegisteredAliasedAsAbstractBaseType)
{
	builder()
		.registerFactory([] { return ConcreteService(); })
		.as<AbstractService>()
		.autoManaged();

	auto& service = container().resolve<AbstractService>();

	ASSERT_TRUE(isOfType<const ConcreteService>(service));
}

TEST_F(ServiceFactoryAsType, ShouldThrowException_WhenResolvingServiceAsItsType_AndServiceFactoryRegisteredOnlyWithAlias)
{
	builder()
		.registerFactory([] { return ConcreteService(); })
		.as<AbstractService>()
		.autoManaged();

	ASSERT_THROW(container().resolve<ConcreteService*>(), DI::Error::ServiceNotRegistered);
}

TEST_F(ServiceFactoryAsType, ShouldResolveServiceAsItsType_WhenServiceFactoryRegisteredWithAliasAndAsSelf)
{
	builder()
		.registerFactory([] { return ConcreteService(); })
		.as<AbstractService>()
		.asSelf()
		.autoManaged();

	auto service = container().resolve<ConcreteService*>();

	ASSERT_NE(nullptr, service);
}
