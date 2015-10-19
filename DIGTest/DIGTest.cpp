#include <gtest/gtest.h>
#include "../DI/ContainerBuilder.h"

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

int main(int argc, char **argv)
{
	auto builder = DI::ContainerBuilder();

	builder.registerInstance(AB());
//	builder.registerType<AB>();

	std::cout << "-----------------" << std::endl;

	auto ab = builder.build().resolve<AB>();
	ab.out();

	std::cout << "-----------------" << std::endl;

	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

