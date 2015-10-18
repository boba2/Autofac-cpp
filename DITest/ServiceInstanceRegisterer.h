#pragma once

#include <memory>
#include "ServiceRegisterer.h"
#include "ServiceInstanceResolver.h"


template<class T>
class ServiceInstanceRegisterer : public ServiceRegisterer<>
{
public:
	template<class U>
	explicit ServiceInstanceRegisterer(U &&instance)
		: _instance(std::make_shared<std::remove_reference_t<U>>(std::forward<U>(instance)))
	{}
	explicit ServiceInstanceRegisterer(T *const instance)
		: _instance(std::shared_ptr<T>(instance, NullDeleter()))
	{}
	explicit ServiceInstanceRegisterer(std::shared_ptr<T> instance)
		: _instance(instance)
	{}
	explicit ServiceInstanceRegisterer(std::unique_ptr<T> instance)
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
