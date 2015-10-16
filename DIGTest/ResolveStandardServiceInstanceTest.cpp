#include "ContainerBaseTest.h"

TEST_F(ContainerBaseTest, container)
{
	ASSERT_EQ(&container(), container().resolve<Container *>());
}