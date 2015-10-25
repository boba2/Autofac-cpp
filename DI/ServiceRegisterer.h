#pragma once

namespace DI
{

	template<class T>
	class ServiceRegisterer
	{
	public:
		explicit ServiceRegisterer(ContainerBuilder* container_builder, std::shared_ptr<T> impl)
			: _container_builder(container_builder), _impl(impl)
		{}

		template<class U>
		auto registerInstance(U &&instance)
		{
			return _container_builder->registerInstance(std::forward<U>(instance));
		}

		template<class U>
		auto registerType()
		{
			return _container_builder->registerType<U>();
		}

		template<class U>
		auto registerFactory(U factory)
		{
			return _container_builder->registerFactory(factory);
		}

		Container build() const
		{
			return _container_builder->build();
		}

	protected:
		ContainerBuilder* const _container_builder;
		std::shared_ptr<T> const _impl;
	};

}