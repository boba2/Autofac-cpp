#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

class Container
{
public:
	explicit Container(void *service_instance)
		: _service_instance(service_instance)
	{}

	void *resolve()
	{
		return _service_instance;
	}

private:
	void *_service_instance;
};

class ContainerBuilder
{
public:
	void registerInstance(void *service_instance)
	{
		_service_instance = service_instance;
	}

	Container build() const
	{
		return Container(_service_instance);
	}

private:
	void *_service_instance;
};

class Class1 {};

TEST_CLASS(BaseContainerTest)
{
public:
	TEST_METHOD(ShouldResolveInstance_WhenInstanceRegistered)
	{
		ContainerBuilder container_builder;

		auto given_service_instance = std::make_unique<Class1>();

		container_builder.registerInstance(given_service_instance.get());

		auto container = container_builder.build();

		auto resolved_service_instance = container.resolve();

		Assert::AreEqual(resolved_service_instance, static_cast<void *>(given_service_instance.get()));
	}
};
