#include <stdafx.h>

#include <gtest/gtest.h>
#include "../DI/ContainerBuilder.h"
#include "../DI/Details/ServiceCreator.h"

struct AB
{
	AB() { std::cout << "Constructing" << std::endl; }
	AB(const AB&) { std::cout << "Copy constructing" << std::endl; }
	AB(AB&&) { std::cout << "Move constructing" << std::endl; }
	virtual ~AB() { std::cout << "Destructing" << std::endl; }

	AB& operator=(const AB&) { std::cout << "Copy assigning" << std::endl; return *this; }
	AB& operator=(AB&&) { std::cout << "Move assigning" << std::endl; return *this; }

	void out() const {}
};

namespace
{
	struct ServiceA1 { int _value; };
	struct ServiceA2 { int _value;  };
	struct ServiceB { ServiceB(ServiceA1 service1, ServiceA2 service2) : _service1(service1), _service2(service2) {} ServiceA1 _service1; ServiceA2 _service2; };
	struct ServiceC { explicit ServiceC(ServiceA1 service1) : _service1(service1) {} ServiceA1 _service1; };
	struct ServiceD { explicit ServiceD(std::shared_ptr<ServiceA1> service1) : _service1(service1) {} std::shared_ptr<ServiceA1> _service1; };
};

template<class T>
using ServiceCreator = DI::Details::ServiceCreator<T>;

int main(int argc, char **argv)
{
	auto builder = DI::ContainerBuilder();
	auto service1 = ServiceA1();
	auto service2 = ServiceA2();
	builder.registerInstance(&service1);
	builder.registerInstance(&service2);

	auto container = builder.build();

	service1._value = 13;
	service2._value = 666;
	auto serviceB = ServiceCreator<ServiceB>::createService(&container);
	std::cout << serviceB._service1._value << std::endl;
	std::cout << serviceB._service2._value << std::endl;

	service1._value = 15;
	auto serviceC = ServiceCreator<ServiceC>::createService<std::shared_ptr<ServiceC>>(&container);
	std::cout << serviceC->_service1._value << std::endl;

	service1._value = 17;
	auto serviceD = ServiceCreator<ServiceD>::createService<std::unique_ptr<ServiceD>>(&container);
	std::cout << serviceD->_service1->_value << std::endl;

	::testing::InitGoogleTest(&argc, argv);

//	return 0;
	return RUN_ALL_TESTS();
}

