#include "ContainerBaseTest.h"

struct ResolveEfficiencyTest : ContainerBaseTest
{
	static std::string _log;
	static bool _logging_enabled;
	void static logMessage(std::string message) { _log += (_log.empty() ? "" : ", ") + message; }
	ResolveEfficiencyTest() { _log.clear(); _logging_enabled = false; }
};

std::string ResolveEfficiencyTest::_log;
bool ResolveEfficiencyTest::_logging_enabled;

namespace
{
	struct DummyService
	{
		DummyService() : _logging_enabled(ResolveEfficiencyTest::_logging_enabled) { logMessage("Constructed"); }
		DummyService(const DummyService&) : _logging_enabled(ResolveEfficiencyTest::_logging_enabled) { logMessage("Copy constructed"); }
		DummyService(DummyService&&) : _logging_enabled(ResolveEfficiencyTest::_logging_enabled) { logMessage("Move constructed"); }
		virtual ~DummyService() { logMessage("Destructed"); }

		DummyService& operator=(const DummyService&) { logMessage("Copy assigned"); return *this; }
		DummyService& operator=(DummyService&&) { logMessage("Move assigned"); return *this; }

		void logMessage(std::string message) const
		{
			if (_logging_enabled)
				ResolveEfficiencyTest::logMessage(message);
		}

		bool _logging_enabled;
	};
}

TEST_F(ResolveEfficiencyTest, ShouldConstructServiceOnlyOnce_WhenResolvingServiceAsCopy_AndServiceRegisteredAsType)
{
	_logging_enabled = true;

	{
		auto container_builder = DI::ContainerBuilder();
		container_builder.registerType<DummyService>();

		auto container = container_builder.build();
		container.resolve<DummyService>();
	}

	ASSERT_EQ("Constructed, Destructed", _log);
}

TEST_F(ResolveEfficiencyTest, ShouldMoveConstructServiceInstance_WhenRegisteringServiceInstanceAsConcreteObject)
{
	_logging_enabled = true;

	{
		auto container_builder = DI::ContainerBuilder();
		container_builder.registerInstance(DummyService());
	}

	ASSERT_EQ("Constructed, Move constructed, Destructed, Destructed", _log);
}

TEST_F(ResolveEfficiencyTest, ShouldCopyConstructService_WhenResolvingServiceAsCopy_AndServiceRegisteredAsInstance)
{
	{
		auto container_builder = DI::ContainerBuilder();
		container_builder.registerInstance(DummyService());

		_logging_enabled = true;

		auto container = container_builder.build();
		container.resolve<DummyService>();
	}

	ASSERT_EQ("Copy constructed, Destructed", _log);
}