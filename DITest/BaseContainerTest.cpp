#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>
#include <typeindex>
#include <unordered_map>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using ServiceInstanceMap = std::unordered_map<std::type_index, void *>;

class ServiceNotRegistered : public std::logic_error
{
public:
	template<class T>
	auto static from_type()
	{
		return ServiceNotRegistered(typeid(T).name());
	}

private:
	explicit ServiceNotRegistered(std::string type_name)
		: logic_error(std::string("Trying to resolve service of an unknown type: ") + type_name)
	{}
};

class Container
{
public:
	explicit Container(const ServiceInstanceMap service_instances)
		: _service_instances(service_instances)
	{}

	template<class T>
	T *resolve()
	{
		if (_service_instances.find(std::type_index(typeid(T))) == _service_instances.end())
			throw ServiceNotRegistered::from_type<T>();

		return static_cast<T *>(_service_instances[std::type_index(typeid(T))]);
	}

private:
	ServiceInstanceMap _service_instances;
};

class ContainerBuilder
{
public:
	template<class T>
	void registerInstance(T *service_instance)
	{
		_service_instances[std::type_index(typeid(T))] = service_instance;
	}

	std::unique_ptr<Container> build() const
	{
		return std::make_unique<Container>(_service_instances);
	}

private:
	ServiceInstanceMap _service_instances;
};

class Class1 {};
class Class2 {};

TEST_CLASS(BaseContainerTest)
{
public:
	TEST_METHOD(ShouldResolveServiceByType_WhenServiceRegistered)
	{
		auto service = std::make_unique<Class1>();

		builder()->registerInstance(service.get());

		Assert::IsTrue(container()->resolve<Class1>() == service.get());
	}

	TEST_METHOD(ShouldResolveServiceOfCorrectType_WhenServicesOfDifferentTypesRegistered)
	{
		auto service1 = std::make_unique<Class1>();
		auto service2 = std::make_unique<Class2>();

		builder()->registerInstance(service1.get());
		builder()->registerInstance(service2.get());

		Assert::IsTrue(container()->resolve<Class1>() == service1.get());
		Assert::IsTrue(container()->resolve<Class2>() == service2.get());
	}

	TEST_METHOD(ShouldThrowException_WhenResolvingServiceOfUnknownType)
	{
		auto service1 = std::make_unique<Class1>();

		builder()->registerInstance(service1.get());

		Assert::ExpectException<ServiceNotRegistered>([this]
		{
			container()->resolve<Class2>();
		});
	}

private:
	ContainerBuilder *builder() const
	{
		return _container_builder.get();
	}

	Container *container()
	{
		return (_container ? _container : _container = builder()->build()).get();
	}

	std::unique_ptr<ContainerBuilder> _container_builder = std::make_unique<ContainerBuilder>();
	std::unique_ptr<Container> _container;
};
