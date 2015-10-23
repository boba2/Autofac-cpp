#pragma once

#include "Details/UnderlyingType.h"
#include "ServiceRegisterer.h"

namespace DI
{

	class ServiceTypeRegistererImpl
	{
	public:
		virtual ~ServiceTypeRegistererImpl() {}

		virtual void setSingleInstance() = 0;
		virtual void setAutoManaged() = 0;
		virtual void registerAlias(std::shared_ptr<Details::ServiceAliasRegisterer<>> alias_registerer) = 0;
	};

	template<class T>
	class ServiceTypeRegisterer : public ServiceRegisterer<ServiceTypeRegistererImpl>
	{
	public:
		static_assert(!std::is_abstract<T>::value, "Cannot register service of an abstract type");
		static_assert(std::is_same<T, typename Details::UnderlyingType<T>::Type>::value, "Cannot register service of a decorated type");

		using ServiceRegisterer::ServiceRegisterer;

		ServiceTypeRegisterer& singleInstance()
		{
			_impl->setSingleInstance();

			return *this;
		}

		ServiceTypeRegisterer& autoManaged()
		{
			_impl->setAutoManaged();

			return *this;
		}

		template<class U>
		ServiceTypeRegisterer& as()
		{
			static_assert(std::is_base_of<U, T>::value, "Alias should be a resolvable base class of the service class being registered");

			_impl->registerAlias(std::make_shared<Details::ServiceAliasRegisterer<U, T>>());

			return *this;
		}

		ServiceTypeRegisterer& asSelf()
		{
			return as<T>();
		}
	};

}