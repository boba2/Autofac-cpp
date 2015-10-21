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
		DummyService() { ResolveEfficiencyTest::logMessage("Constructed"); }
		DummyService(const DummyService&) { ResolveEfficiencyTest::logMessage("Copy constructed"); }
		DummyService(DummyService&&) { ResolveEfficiencyTest::logMessage("Move constructed"); }
		virtual ~DummyService() { ResolveEfficiencyTest::logMessage("Destructed"); }

		DummyService& operator=(const DummyService&) { ResolveEfficiencyTest::logMessage("Copy assigned"); return *this; }
		DummyService& operator=(DummyService&&) { ResolveEfficiencyTest::logMessage("Move assigned"); return *this; }
	};
}

TEST_F(ResolveEfficiencyTest, Should_)
{
	{
		auto container_builder = DI::ContainerBuilder();
		container_builder.registerType<DummyService>();
		container_builder.build().resolve<DummyService>();
	}

	ASSERT_EQ("Constructed, Destructed", log);
}

TEST_F(ResolveEfficiencyTest, Should_2)
{
	{
		auto container_builder = DI::ContainerBuilder();
		container_builder.registerInstance(DummyService());
	}

	ASSERT_EQ("Constructed, Move constructed, Destructed, Destructed", log);
}

TEST_F(ResolveEfficiencyTest, Should_3)
{
	{
		auto container_builder = DI::ContainerBuilder();
		container_builder.registerInstance(DummyService());
		container_builder.build().resolve<std::shared_ptr<DummyService>>();
	}

	ASSERT_EQ("Constructed, Move constructed, Destructed, Destructed", log);
}