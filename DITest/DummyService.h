#pragma once

template<int = 0>
class DummyService
{
	using Logger = Microsoft::VisualStudio::CppUnitTestFramework::Logger;

public:
	explicit DummyService(const int value = 0)
		: _value(value)
	{
		Logger::WriteMessage("Constructing");
	}

	DummyService(const DummyService &other)
		: _value(other._value)
	{
		Logger::WriteMessage("Copy constructing");
	}

	DummyService(DummyService &&other)
	{
		Logger::WriteMessage("Move constructing");

		std::swap(_value, other._value);
	}

	DummyService &operator=(const DummyService &other)
	{
		Logger::WriteMessage("Copy assigning");

		_value = other._value;

		return *this;
	}

	DummyService &operator=(DummyService &&other)
	{
		Logger::WriteMessage("Move assigning");

		std::swap(_value, other._value);

		return *this;
	}

	virtual ~DummyService()
	{
		Logger::WriteMessage("Destroying");
	}

	int _value;
};
