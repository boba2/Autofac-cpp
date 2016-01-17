#include <stdafx.h>
#include "ContainerBaseTest.h"
#include "../DI/Error/ServiceNotRegistered.h"

namespace
{
	struct ServiceA { virtual ~ServiceA() {} };
	struct ServiceB {};
	struct SpecialService : ServiceA {};

	struct AbstractService { virtual ~AbstractService() {}; virtual void abstract() = 0; };
	struct ConcreteService : AbstractService { virtual void abstract() override {} };
}

using ServiceTypeAsTypeTest = ContainerBaseTest;

TEST_F(ServiceTypeAsTypeTest, ShouldResolveServiceAsBaseTypeAsPtr_WhenServiceTypeRegisteredAliasedAsBaseType)
{
	builder()
		.registerType<SpecialService>()
		.as<ServiceA>()
		.autoManaged();

	auto resolved = container().resolve<ServiceA*>();

	ASSERT_TRUE(isOfType<SpecialService>(resolved));
}

TEST_F(ServiceTypeAsTypeTest, ShouldResolveServiceAsBaseTypeAsPtr_WhenServiceTypeRegisteredAliasedAsAbstractBaseType)
{
	builder()
		.registerType<ConcreteService>()
		.as<AbstractService>()
		.autoManaged();

	auto resolved = container().resolve<AbstractService*>();

	ASSERT_TRUE(isOfType<ConcreteService>(resolved));
}

TEST_F(ServiceTypeAsTypeTest, ShouldResolveServiceAsBaseTypeAsConstRef_WhenServiceTypeRegisteredAliasedAsAbstractBaseType)
{
	builder()
		.registerType<ConcreteService>()
		.as<AbstractService>()
		.autoManaged();

	auto& resolved = container().resolve<AbstractService>();

	ASSERT_TRUE(isOfType<const ConcreteService>(resolved));
}

TEST_F(ServiceTypeAsTypeTest, ShouldThrowException_WhenResolvingServiceAsItsType_AndServiceTypeRegisteredOnlyWithAlias)
{
	builder()
		.registerType<ConcreteService>()
		.as<AbstractService>()
		.autoManaged();

	ASSERT_THROW(container().resolve<ConcreteService*>(), DI::Error::ServiceNotRegistered);
}

TEST_F(ServiceTypeAsTypeTest, ShouldResolveServiceAsItsType_WhenServiceTypeRegisteredWithAliasAndAsSelf)
{
	builder()
		.registerType<ConcreteService>()
		.as<AbstractService>()
		.asSelf()
		.autoManaged();

	auto resolved = container().resolve<ConcreteService*>();

	ASSERT_TRUE(resolved != nullptr);
}