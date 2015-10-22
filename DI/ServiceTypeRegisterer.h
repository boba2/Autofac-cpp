#pragma once

namespace DI
{

	template<class T>
	class ServiceTypeRegisterer
	{
	public:
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