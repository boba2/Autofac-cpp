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
	template<class U>
	explicit ServiceInstanceHolder(U &&instance)
		: _instance(std::make_shared<std::remove_reference_t<U>>(std::forward<U>(instance)))
	{}
	explicit ServiceInstanceHolder(T *const instance)
		: _instance(std::shared_ptr<T>(instance, NullDeleter()))
	{}
	explicit ServiceInstanceHolder(std::shared_ptr<T> instance)
		: _instance(instance)
	{}
	explicit ServiceInstanceHolder(std::unique_ptr<T> instance)
		: _instance(std::move(instance))
	{}

	std::shared_ptr<T> get()
	{
		return _instance;
	}

private:
	struct NullDeleter
	{
		void operator()(T *) const {}
	};

	std::shared_ptr<T> _instance;
};
