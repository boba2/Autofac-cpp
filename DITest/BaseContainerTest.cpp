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

	template<class T>
	T *resolve()
	{
		return static_cast<T *>(_service_instance);
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
	TEST_METHOD(ShouldResolveInstanceByType_WhenInstanceRegistered)
	{
		ContainerBuilder container_builder;

		auto given_service_instance = std::make_unique<Class1>();

		container_builder.registerInstance(given_service_instance.get());

		auto container = container_builder.build();

		auto resolved_service_instance = container.resolve<Class1>();

		Assert::IsTrue(resolved_service_instance == given_service_instance.get());
	}
};
