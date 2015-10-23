#pragma once

namespace DI
{

	class ServiceFactoryRegistererImpl
	{
	public:
		virtual ~ServiceFactoryRegistererImpl() {}

		virtual void setAutoManaged() = 0;
		virtual void registerAlias(std::shared_ptr<Details::ServiceAliasRegisterer<>> alias_registerer) = 0;
	};

	template<class T>
	class ServiceFactoryRegisterer
	{
	public:
		explicit ServiceFactoryRegisterer(std::shared_ptr<ServiceFactoryRegistererImpl> impl)
			: _impl(impl)
		{}

		ServiceFactoryRegisterer& autoManaged()
		{
			_impl->setAutoManaged();

			return *this;
		}

	private:
		std::shared_ptr<ServiceFactoryRegistererImpl> const _impl;
	};

}