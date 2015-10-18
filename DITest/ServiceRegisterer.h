#pragma once

#include <memory>

template<class T>
class ServiceResolver;

template<class T = void>
class ServiceRegisterer;

template<>
class ServiceRegisterer<void>
{
public:
	virtual ~ServiceRegisterer() {}

	virtual std::shared_ptr<ServiceResolver<>> getServiceResolver() const = 0;
};
