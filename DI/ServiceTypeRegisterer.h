#pragma once

#include "Details/UnderlyingType.h"

namespace DI
{

	template<class T>
	class ServiceTypeRegisterer
	{
	public:
		using Type = ServiceTypeRegisterer;

		static_assert(!std::is_abstract<T>::value, "Cannot register service of an abstract type");
		static_assert(std::is_same<T, typename Details::UnderlyingType<T>::Type>::value, "Cannot register service of a decorated type");

		ServiceTypeRegisterer& singleInstance()
		{
			setSingleInstance();

			return *this;
		}

		ServiceTypeRegisterer& autoManaged()
		{
			setAutoManaged();

			return *this;
		}

		template<class U>
		ServiceTypeRegisterer& as()
		{
			static_assert(std::is_base_of<U, T>::value, "Alias should be a resolvable base class of the service class being registered");

			registerAlias(std::make_shared<Details::ServiceAliasRegisterer<U, T>>());

			return *this;
		}

		ServiceTypeRegisterer& asSelf()
		{
			return as<T>();
		}

	protected:
		virtual void setSingleInstance() = 0;
		virtual void setAutoManaged() = 0;
		virtual void registerAlias(std::shared_ptr<Details::ServiceAliasRegisterer<>> alias_registerer) = 0;
	};

}