#pragma once

#include <memory>
#include "Error.h"

template<class T>
struct ServiceInstanceReferenceTypeConverter
{
	static const T &convert(std::shared_ptr<T> instance)
	{
		return *instance.get();
	}
};

template<class T>
struct ServiceInstanceReferenceTypeConverter<T &>
{
	static T &convert(std::shared_ptr<T> instance)
	{
		return *instance.get();
	}
};

template<class T>
struct ServiceInstanceReferenceTypeConverter<T *>
{
	static T *convert(std::shared_ptr<T> instance)
	{
		return instance.get();
	}
};

template<class T>
struct ServiceInstanceReferenceTypeConverter<std::shared_ptr<T>>
{
	static std::shared_ptr<T> convert(std::shared_ptr<T> instance)
	{
		return instance;
	}
};

template<class T>
struct ServiceInstanceReferenceTypeConverter<std::shared_ptr<T> &> : ServiceInstanceReferenceTypeConverter<std::shared_ptr<T>> {};

template<class T>
struct ServiceInstanceReferenceTypeConverter<std::unique_ptr<T>>
{
	static std::unique_ptr<T> convert(std::shared_ptr<T>)
	{
		throw Error::ServiceInstanceNotResolvableAsUniquePtr();
	}
};
