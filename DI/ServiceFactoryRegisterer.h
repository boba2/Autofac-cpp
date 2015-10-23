#pragma once

namespace DI
{

	template<class T>
	class ServiceFactoryRegisterer
	{
	public:
		ServiceFactoryRegisterer& autoManaged()
		{
			setAutoManaged();

			return *this;
		}

	protected:
		virtual void setAutoManaged() = 0;
		virtual void registerAlias(std::shared_ptr<Details::ServiceAliasRegisterer<>> alias_registerer) = 0;
	};

}