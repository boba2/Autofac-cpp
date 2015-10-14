#pragma once

#include <memory>
#include "Error.h"

template<class T>
struct ServiceInstanceReferenceTypeConverter
{
	static std::shared_ptr<T> convert(T &&instance)
	{
		return std::make_shared<T>(std::forward<T>(instance));
	}

	static const T &convert(std::shared_ptr<T> instance)
	{
		return *instance.get();
	}
};

template<class T>
struct ServiceInstanceReferenceTypeConverter<T &>
{
	static std::shared_ptr<T> convert(const T &instance)
	{
		return std::make_shared<T>(instance);
	}

	static T &convert(std::shared_ptr<T> instance)
	{
		return *instance.get();
	}
};

template<class T>
struct ServiceInstanceReferenceTypeConverter<T *>
{
	static std::shared_ptr<T> convert(T *instance)
	{
		return std::shared_ptr<T>(instance, NullDeleter());
	}

	static T *convert(std::shared_ptr<T> instance)
	{
		return instance.get();
	}

private:
	struct NullDeleter
	{
		void operator()(T *) const {}
	};
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
	static std::shared_ptr<T> convert(std::unique_ptr<T> instance)
	{
		return std::move(instance);
	}

	static std::unique_ptr<T> convert(std::shared_ptr<T>)
	{
		throw Error::ServiceInstanceNotResolvableAsUniquePtr();
	}
};
