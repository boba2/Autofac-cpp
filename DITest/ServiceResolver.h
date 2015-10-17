#pragma once

#include <memory>

template<class T = void>
class ServiceResolver;

template<>
class ServiceResolver<void>
{
public:
	virtual ~ServiceResolver() {}
};

template<class T>
class ServiceResolver : public ServiceResolver<>
{
public:
	virtual std::shared_ptr<T> get() = 0;
};