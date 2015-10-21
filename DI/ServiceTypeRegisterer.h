#pragma once

#include "ServiceRegisterer.h"

namespace DI
{

	template<class T>
	class ServiceTypeRegisterer : public virtual ServiceRegisterer<T>
	{
	public:
		ServiceTypeRegisterer& singleInstance()
		{
			setSingleInstance();

			return *this;
		}

		template<class U>
		ServiceTypeRegisterer& as()
		{
			static_cast<ServiceRegisterer<T>&>(*this).as<U>(); // this made that complicated due to g++14 reporting error

			return *this;
		}

		ServiceTypeRegisterer& asSelf()
		{
			ServiceRegisterer<T>::asSelf();

			return *this;
		}

	protected:
		virtual void setSingleInstance() = 0;
	};

}