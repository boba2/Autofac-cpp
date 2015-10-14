#pragma once

#include <memory>

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
	explicit ServiceInstanceHolder(std::shared_ptr<T> instance)
		: _instance(instance)
	{}

	std::shared_ptr<T> get()
	{
		return _instance;
	}

private:
	std::shared_ptr<T> _instance;
};
