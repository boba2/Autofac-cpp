#include "ContainerBaseTest.h"
#include "DummyService.h"

class SpecialDummyService : public DummyService
{
	using DummyService::DummyService;
};

TEST_F(ContainerBaseTest, ShouldResolveServiceByBaseType_WhenServiceInstanceRegistered)
{
	SpecialDummyService service;

	builder()
		.registerInstance(&service)
		.as<DummyService>();

	ASSERT_EQ(&service, container().resolve<DummyService *>());
}