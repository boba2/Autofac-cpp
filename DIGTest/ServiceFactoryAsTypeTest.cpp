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

TEST_F(ServiceFactoryAsType, ShouldBreakStaticAssert_WhenRegisteringServiceFactoryAliasedAsUnrelatedType)
{
//	builder()
//		.registerFactory([] { return ServiceA(); })
//		.as<ServiceB>();
}

TEST_F(ServiceFactoryAsType, ShouldResolveServiceAsBaseTypeAsPtr_WhenServiceFactoryRegisteredAliasedAsBaseType)
{
	builder()
		.registerFactory([] { return SpecialService(); })
		.as<ServiceA>()
		.autoManaged();

	ASSERT_TRUE(dynamic_cast<SpecialService*>(container().resolve<ServiceA*>()) != nullptr);
}

TEST_F(ServiceFactoryAsType, ShouldResolveServiceAsBaseTypeAsPtr_WhenServiceFactoryRegisteredAliasedAsAbstractBaseType)
{
	builder()
		.registerFactory([] { return ConcreteService(); })
		.as<AbstractService>()
		.autoManaged();

	ASSERT_TRUE(dynamic_cast<ConcreteService*>(container().resolve<AbstractService*>()) != nullptr);
}

TEST_F(ServiceFactoryAsType, ShouldResolveServiceAsBaseTypeAsConstRef_WhenServiceFactoryRegisteredAliasedAsAbstractBaseType)
{
	builder()
		.registerFactory([] { return ConcreteService(); })
		.as<AbstractService>()
		.autoManaged();

	auto& service = container().resolve<AbstractService>();

	ASSERT_TRUE(dynamic_cast<const ConcreteService*>(&service) != nullptr);
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

	ASSERT_TRUE(container().resolve<ConcreteService*>() != nullptr);
}
