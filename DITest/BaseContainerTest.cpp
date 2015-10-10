#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>
#include <typeindex>
#include <unordered_map>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

class Container
{
public:
	explicit Container(std::unordered_map<std::type_index, void *> service_instances)
		: _service_instances(service_instances)
	{}

	template<class T>
	T *resolve()
	{
		return static_cast<T *>(_service_instances[std::type_index(typeid(T))]);
	}

private:
	std::unordered_map<std::type_index, void *> _service_instances;
};

class ContainerBuilder
{
public:
	template<class T>
	void registerInstance(T *service_instance)
	{
		_service_instances[std::type_index(typeid(T))] = service_instance;
	}

	Container build() const
	{
		return Container(_service_instances);
	}

private:
	std::unordered_map<std::type_index, void *> _service_instances;
};

class Class1 {};
class Class2 {};

TEST_CLASS(BaseContainerTest)
{
public:
	TEST_METHOD(ShouldResolveServiceByType_WhenServiceRegistered)
	{
		ContainerBuilder container_builder;

		auto given_service = std::make_unique<Class1>();

		container_builder.registerInstance(given_service.get());

		auto container = container_builder.build();

		auto resolved_service = container.resolve<Class1>();

		Assert::IsTrue(resolved_service == given_service.get());
	}

	TEST_METHOD(ShouldResolveServiceOfCorrectType_WhenServicesOfDifferentTypesRegistered)
	{
		ContainerBuilder container_builder;

		auto given_service1 = std::make_unique<Class1>();
		auto given_service2 = std::make_unique<Class2>();

		container_builder.registerInstance(given_service1.get());
		container_builder.registerInstance(given_service2.get());

		auto container = container_builder.build();

		auto resolved_service1 = container.resolve<Class1>();
		auto resolved_service2 = container.resolve<Class2>();

		Assert::IsTrue(resolved_service1 == given_service1.get());
		Assert::IsTrue(resolved_service2 == given_service2.get());
	}
};
