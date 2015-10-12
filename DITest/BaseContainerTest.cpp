#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>
#include <typeindex>
#include <unordered_map>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Error {

class ServiceNotRegistered : public std::logic_error
{
public:
	template<class T>
	auto static fromType()
	{
		return ServiceNotRegistered(typeid(T).name());
	}

private:
	explicit ServiceNotRegistered(std::string type_name)
		: logic_error(std::string("Trying to resolve service of an unknown type: ") + type_name)
	{}
};

}

template<class T>
struct UnderlyingType
{
	using Type = T;
};

template<class T>
struct UnderlyingType<T *>
{
	using Type = typename UnderlyingType<T>::Type;
};

template<class T>
struct UnderlyingType<T &>
{
	using Type = typename UnderlyingType<T>::Type;
};

template<class T>
struct UnderlyingType<std::shared_ptr<T>>
{
	using Type = typename UnderlyingType<T>::Type;
};

template<class T = void>
class ServiceInstanceHolder;

template<>
class ServiceInstanceHolder<void>
{
public:
	virtual ~ServiceInstanceHolder() {};
};

template<class T>
class ServiceInstanceHolder : public ServiceInstanceHolder<>
{
public:
	virtual T *serviceInstance() = 0;
};

template<class T>
class ConcreteServiceInstanceHolder : public ServiceInstanceHolder<T>
{
public:
	explicit ConcreteServiceInstanceHolder(const T &service_instance)
		: _service_instance(service_instance)
	{}

	virtual T *serviceInstance() override
	{
		return &_service_instance;
	}

private:
	T _service_instance;
};

template<class T>
class ConcreteServiceInstanceHolder<T *> : public ServiceInstanceHolder<T>
{
public:
	explicit ConcreteServiceInstanceHolder(T *const service_instance_ptr)
		: _service_instance_ptr(service_instance_ptr)
	{}

	virtual T *serviceInstance() override
	{
		return _service_instance_ptr;
	}

private:
	T *const _service_instance_ptr;
};

template<class T>
class ConcreteServiceInstanceHolder<std::shared_ptr<T>> : public ServiceInstanceHolder<T>
{
public:
	explicit ConcreteServiceInstanceHolder(std::shared_ptr<T> service_instance_sptr)
		: _service_instance_sptr(service_instance_sptr)
	{}

	virtual T *serviceInstance() override
	{
		return _service_instance_sptr.get();
	}

private:
	std::shared_ptr<T> const _service_instance_sptr;
};

template<class T>
struct TypeIndex
{
	static const std::type_index value;
};

template<class T>
const std::type_index TypeIndex<T>::value = std::type_index{ typeid(UnderlyingType<T>::Type) };

class ServiceInstances
{
public:
	template<class T>
	void add(T &&service_instance)
	{
		_service_instances[TypeIndex<T>::value] = std::make_shared<ConcreteServiceInstanceHolder<std::remove_reference_t<T>>>(service_instance);
	}

	template<class T>
	bool has()
	{
		return _service_instances.find(TypeIndex<T>::value) != _service_instances.end();
	}

	template<class T>
	T *get() 
	{
		return dynamic_cast<ServiceInstanceHolder<T> *>(_service_instances.at(TypeIndex<T>::value).get())->serviceInstance();
	}

private:
	std::unordered_map<std::type_index, std::shared_ptr<ServiceInstanceHolder<>>> _service_instances;
};

class Container
{
public:
	explicit Container(const ServiceInstances service_instances)
		: _service_instances(service_instances)
	{}

	template<class T>
	T resolve()
	{
		if (!_service_instances.has<typename UnderlyingType<T>::Type>())
			throw Error::ServiceNotRegistered::fromType<typename UnderlyingType<T>::Type>();


		return _service_instances.get<typename UnderlyingType<T>::Type>();
	}

private:
	ServiceInstances _service_instances;
};

class ContainerBuilder
{
public:
	template<class T>
	void registerInstance(T &&service_instance)
	{
		_service_instances.add(std::forward<T>(service_instance));
	}

	std::unique_ptr<Container> build() const
	{
		return std::make_unique<Container>(_service_instances);
	}

private:
	ServiceInstances _service_instances;
};

template<int = 0>
class DummyService
{
public:
	explicit DummyService(const int value = 0)
		: _value(value)
	{}
	virtual ~DummyService() {}

	const int _value;
};

TEST_CLASS(BaseContainerTest)
{
public:
	TEST_METHOD(ShouldResolveServiceByType_WhenServiceRegisteredThroughPointer)
	{
		DummyService<1> service;

		builder()->registerInstance(&service);

		Assert::IsTrue(container()->resolve<DummyService<1> *>() == &service);
	}

	TEST_METHOD(ShouldResolveServiceOfCorrectType_WhenServicesOfDifferentTypesRegisteredThroughPointers)
	{
		DummyService<1> service1;
		DummyService<2> service2;

		builder()->registerInstance(&service1);
		builder()->registerInstance(&service2);

		Assert::IsTrue(container()->resolve<DummyService<1> *>() == &service1);
		Assert::IsTrue(container()->resolve<DummyService<2> *>() == &service2);
	}

	TEST_METHOD(ShouldThrowException_WhenResolvingServiceOfUnregisteredType)
	{
		DummyService<1> service1;

		builder()->registerInstance(&service1);

		Assert::ExpectException<Error::ServiceNotRegistered>([this]
		{
			container()->resolve<DummyService<2> *>();
		});
	}

	TEST_METHOD(ShouldResolveCopyOfService_WhenServiceInstanceRegistered)
	{
		builder()->registerInstance(DummyService<>(13));

		Assert::AreEqual(13, container()->resolve<DummyService<> *>()->_value);
	}

	TEST_METHOD(ShouldResolveCopyOfServiceOfCorrectType_WhenServiceInstancesOfDifferentTypesRegistered)
	{
		builder()->registerInstance(DummyService<1>(13));
		builder()->registerInstance(DummyService<2>(14));

		Assert::AreEqual(13, container()->resolve<DummyService<1> *>()->_value);
		Assert::AreEqual(14, container()->resolve<DummyService<2> *>()->_value);
	}

	TEST_METHOD(ShouldResolveServiceByType_WhenServiceRegisteredThroughSharedPtr)
	{
		auto service = std::make_shared<DummyService<1>>();

		builder()->registerInstance(service);

		Assert::IsTrue(container()->resolve<DummyService<1> *>() == service.get());
	}

	TEST_METHOD(ShouldResolveServiceOfCorrectType_WhenServiceInstancesOfDifferentTypesRegisteredThroughSharedPtr)
	{
		auto service1 = std::make_shared<DummyService<1>>();
		auto service2 = std::make_shared<DummyService<2>>();

		builder()->registerInstance(service1);
		builder()->registerInstance(service2);

		Assert::IsTrue(container()->resolve<DummyService<1> *>() == service1.get());
		Assert::IsTrue(container()->resolve<DummyService<2> *>() == service2.get());
	}

	TEST_METHOD(ShouldHoldServiceInstance_WhenRegisteredReferenceDestroyed)
	{
		builder()->registerInstance(std::make_shared<DummyService<1>>(15));

		Assert::AreEqual(15, container()->resolve<DummyService<1> *>()->_value);
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
