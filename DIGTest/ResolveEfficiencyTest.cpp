#include <stdafx.h>

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
	struct LoggingService
	{
		LoggingService() : _logging_enabled(ResolveEfficiencyTest::_logging_enabled) { logMessage("Constructed"); }
		LoggingService(const LoggingService&) : _logging_enabled(ResolveEfficiencyTest::_logging_enabled) { logMessage("Copy constructed"); }
		LoggingService(LoggingService&&) : _logging_enabled(ResolveEfficiencyTest::_logging_enabled) { logMessage("Move constructed"); }
		virtual ~LoggingService() { logMessage("Destructed"); }

		LoggingService& operator=(const LoggingService&) { logMessage("Copy assigned"); return *this; }
		LoggingService& operator=(LoggingService&&) { logMessage("Move assigned"); return *this; }

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
		container_builder.registerType<LoggingService>();

		auto container = container_builder.build();
		container.resolve<LoggingService>();
	}

	ASSERT_EQ("Constructed, Destructed", _log);
}

TEST_F(ResolveEfficiencyTest, ShouldMoveConstructServiceInstance_WhenRegisteringServiceInstanceAsConcreteObject)
{
	{
		auto service = LoggingService();

		_logging_enabled = true;

		auto container_builder = DI::ContainerBuilder();
		container_builder.registerInstance(std::move(service));
	}

	ASSERT_EQ("Move constructed, Destructed", _log);
}

TEST_F(ResolveEfficiencyTest, ShouldCopyConstructService_WhenResolvingServiceAsCopy_AndServiceRegisteredAsInstance)
{
	{
		auto container_builder = DI::ContainerBuilder();
		container_builder.registerInstance(LoggingService());

		_logging_enabled = true;

		auto container = container_builder.build();
		container.resolve<LoggingService>();
	}

	ASSERT_EQ("Copy constructed, Destructed", _log);
}