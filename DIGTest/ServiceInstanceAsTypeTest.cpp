#include <stdafx.h>

#include "ContainerBaseTest.h"
#include "../DI/Error/ServiceNotResolvableAs.h"
#include "../DI/Error/ServiceNotRegistered.h"

namespace
{
	struct BaseService { virtual ~BaseService() {} };
	struct ServiceA : virtual BaseService { int _value; };
	struct ServiceB : virtual BaseService {};
	struct SpecialService : ServiceA, ServiceB {};
}

using ServiceInstanceAsTypeTest = ContainerBaseTest;

TEST_F(ServiceInstanceAsTypeTest, ShouldResolveServiceAsBaseType_WhenServiceInstanceRegisteredAliasedAsBaseType)
{
	auto service = SpecialService();

	builder()
		.registerInstance(&service)
		.as<ServiceA>();

	auto resolved = container().resolve<ServiceA *>();

	ASSERT_EQ(&service, resolved);
}

TEST_F(ServiceInstanceAsTypeTest, ShouldResolveServiceAsAnyBaseType_WhenServiceInstanceRegisteredAliasedAsManyBaseTypes)
{
	auto service = SpecialService();

	builder()
		.registerInstance(&service)
		.as<ServiceA>()
		.as<ServiceB>();

	auto resolvedA = container().resolve<ServiceA *>();
	auto resolvedB = container().resolve<ServiceB *>();

	ASSERT_EQ(&service, resolvedA);
	ASSERT_EQ(&service, resolvedB);
}

TEST_F(ServiceInstanceAsTypeTest, ShouldThrowException_WhenResolvingServiceAsItsType_AndServiceInstanceRegisteredOnlyWithAlias)
{
	auto service = SpecialService();

	builder()
		.registerInstance(&service)
		.as<ServiceA>();

	ASSERT_THROW(container().resolve<SpecialService *>(), DI::Error::ServiceNotRegistered);
}

TEST_F(ServiceInstanceAsTypeTest, ShouldResolveServiceAsItsType_WhenServiceInstanceRegisteredOnlyAliasedAsItsOwnType)
{
	auto service = SpecialService();

	builder()
		.registerInstance(&service)
		.as<SpecialService>();

	auto resolved = container().resolve<SpecialService *>();

	ASSERT_EQ(&service, resolved);
}

TEST_F(ServiceInstanceAsTypeTest, ShouldResolveServiceAsItsType_WhenServiceInstanceRegisteredWithAliasAndAsSelf)
{
	auto service = SpecialService();

	builder()
		.registerInstance(&service)
		.as<ServiceA>()
		.asSelf();

	auto resolved = container().resolve<SpecialService *>();

	ASSERT_EQ(&service, resolved);
}

TEST_F(ServiceInstanceAsTypeTest, ShouldResolveServiceAsBaseType_WhenServiceInstanceRegisteredAliasedAsBaseTypeAndAsSelf)
{
	auto service = SpecialService();

	builder()
		.registerInstance(&service)
		.as<ServiceA>()
		.asSelf();

	auto resolved = container().resolve<ServiceA *>();

	ASSERT_EQ(&service, resolved);
}

TEST_F(ServiceInstanceAsTypeTest, ShouldResolveServiceAsItsType_WhenServiceInstanceRegisteredOnlyAsSelf)
{
	auto service = SpecialService();

	builder()
		.registerInstance(&service)
		.asSelf();

	auto resolved = container().resolve<SpecialService *>();

	ASSERT_EQ(&service, resolved);
}

TEST_F(ServiceInstanceAsTypeTest, ShouldResolveServiceAsBaseTypeAsCopy_WhenServiceInstanceRegisteredAliasedAsBaseType)
{
	auto service = SpecialService();
	service._value = 13;

	builder()
		.registerInstance(&service)
		.as<ServiceA>();

	auto resolved = container().resolve<ServiceA>();

	ASSERT_EQ(13, resolved._value);
}

TEST_F(ServiceInstanceAsTypeTest, ShouldResolveServiceAsBaseTypeAsReference_WhenServiceInstanceRegisteredAliasedAsBaseType)
{
	auto service = SpecialService();

	builder()
		.registerInstance(&service)
		.as<ServiceA>();

	auto& resolved = container().resolve<ServiceA &>();

	ASSERT_EQ(&service, &resolved);
}

TEST_F(ServiceInstanceAsTypeTest, ShouldResolveServiceAsBaseTypeAsSharedPtr_WhenServiceInstanceRegisteredAliasedAsBaseType)
{
	auto service = SpecialService();

	builder()
		.registerInstance(&service)
		.as<ServiceA>();

	auto resolved = container().resolve<std::shared_ptr<ServiceA>>();

	ASSERT_EQ(&service, resolved.get());
}

TEST_F(ServiceInstanceAsTypeTest, ShouldThrowException_WhenResolvingServiceAsBaseTypeAsUniquePtr_AndServiceInstanceRegisteredAliasedAsBaseType)
{
	auto service = SpecialService();

	builder()
		.registerInstance(&service)
		.as<ServiceA>();

	ASSERT_THROW(container().resolve<std::unique_ptr<ServiceA>>(), DI::Error::ServiceNotResolvableAs);
}

TEST_F(ServiceInstanceAsTypeTest, ShouldResolveServiceAsVirtualBaseType_WhenServiceInstanceRegisteredWithAliasedAsVirtualBaseType)
{
	auto service = SpecialService();

	builder()
		.registerInstance(&service)
		.as<BaseService>();

	auto resolved = container().resolve<BaseService *>();

	ASSERT_EQ(&service, dynamic_cast<SpecialService *>(resolved));
}