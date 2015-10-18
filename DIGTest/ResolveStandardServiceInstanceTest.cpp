#include "ContainerBaseTest.h"

TEST_F(ContainerBaseTest, ShouldResolveContainerInstance)
{
	ASSERT_EQ(&container(), container().resolve<DI::Container *>());
}