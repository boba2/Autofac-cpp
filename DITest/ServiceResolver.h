#pragma once

#include <memory>

template<class T = void>
class ServiceResolver;

template<>
class ServiceResolver<void>
{
public:
	virtual ~ServiceResolver() {}

	virtual TypeIndex<> getServiceType() const = 0;
};

template<class T>
class ServiceResolver : public ServiceResolver<>
{
public:
	virtual std::shared_ptr<T> getService() const = 0;
};