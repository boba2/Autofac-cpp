#pragma once

namespace DI
{
	class ContainerBuilder;

	template<class T>
	class ServiceRegisterer
	{
	public:
		explicit ServiceRegisterer(ContainerBuilder* container_builder, std::shared_ptr<T> impl)
			: _container_builder(container_builder), _impl(impl)
		{}

		template<class U>
		auto registerInstance(U &&instance);

		template<class U>
		auto registerType();

		template<class U>
		auto registerFactory(U factory);

		Container build() const;

	protected:
		std::shared_ptr<T> const _impl;

	private:
		ContainerBuilder* const _container_builder;
	};

}

#include "ServiceRegisterer.i"