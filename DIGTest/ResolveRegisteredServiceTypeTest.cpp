#include "ContainerBaseTest.h"

class DummyService {};

TEST_F(ContainerBaseTest, Should)
{
	builder().registerType<DummyService>();

	ASSERT_TRUE(dynamic_cast<DummyService *>(container().resolve<DummyService *>()) != nullptr);
}