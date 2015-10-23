#pragma once

namespace DI
{

	template<class T>
	class ServiceRegisterer
	{
	public:
		explicit ServiceRegisterer(std::shared_ptr<T> impl)
			: _impl(impl)
		{}

	protected:
		std::shared_ptr<T> const _impl;
	};

}