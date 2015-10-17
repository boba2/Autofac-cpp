#pragma once

#include <memory>
#include "ServiceInstanceResolver.h"


template<class T = void>
class ServiceInstanceHolder;

template<>
class ServiceInstanceHolder<void>
{
public:
	virtual ~ServiceInstanceHolder() {};

	virtual std::shared_ptr<ServiceResolver<>> getServiceResolver() const = 0;
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

	std::shared_ptr<ServiceResolver<>> getServiceResolver() const override
	{
		return std::make_shared<ServiceInstanceResolver<T>>(_instance);
	}

private:
	struct NullDeleter
	{
		void operator()(T *) const {}
	};

	std::shared_ptr<T> _instance;
};
