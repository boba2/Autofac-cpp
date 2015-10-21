#include "ContainerBaseTest.h"

struct ResolveEfficiencyTest : ContainerBaseTest
{
	static std::string log;
	void static logMessage(std::string message) { log += (log.empty() ? "" : ", ") + message; }
	ResolveEfficiencyTest() { log.clear(); }
};

std::string ResolveEfficiencyTest::log;

namespace
{
	struct DummyService
	{
		DummyService() { logMessage("Constructed"); }
		DummyService(const DummyService&) { logMessage("Copy constructed"); }
		DummyService(DummyService&&) { logMessage("Move constructed"); }
		virtual ~DummyService() { logMessage("Destructed"); }

		DummyService& operator=(const DummyService&) { logMessage("Copy assigned"); return *this; }
		DummyService& operator=(DummyService&&) { logMessage("Move assigned"); return *this; }

		void logMessage(std::string message) const
		{
				ResolveEfficiencyTest::logMessage(message);
		}
	};
}

TEST_F(ResolveEfficiencyTest, ShouldConstructServiceOnlyOnce_WhenResolvingServiceByCopy_AndServiceRegisteredByType)
{
	{
		auto container_builder = DI::ContainerBuilder();
		container_builder.registerType<DummyService>();

		auto container = container_builder.build();
		container.resolve<DummyService>();
	}

	ASSERT_EQ("Constructed, Destructed", log);
}

TEST_F(ResolveEfficiencyTest, ShouldMoveConstructServiceInstance_WhenRegisteringServiceInstanceByConcreteObject)
{
	{
		auto container_builder = DI::ContainerBuilder();
		container_builder.registerInstance(DummyService());
	}

	ASSERT_EQ("Constructed, Move constructed, Destructed, Destructed", log);
}

TEST_F(ResolveEfficiencyTest, ShouldCopyConstructService_WhenResolvingServiceByCopy_AndServiceRegisteredByInstance)
{
	{
		auto container_builder = DI::ContainerBuilder();
		container_builder.registerInstance(DummyService());

		auto container = container_builder.build();
		container.resolve<DummyService>();
	}

	ASSERT_EQ("Constructed, Move constructed, Destructed, Copy constructed, Destructed, Destructed", log);
}