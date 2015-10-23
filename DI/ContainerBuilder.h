#pragma once

#include "Container.h"
#include "Details/ServiceInstanceRegisterer.h"
#include "Details/ServiceTypeRegisterer.h"
#include "Details/ServiceFactoryRegisterer.h"

namespace DI
{

	class ContainerBuilder
	{
	public:
		template<class T>
		auto& registerInstance(T &&instance)
		{
			using Registerer = Details::ServiceInstanceRegisterer<typename Details::UnderlyingType<T>::Type>;

			auto registerer = std::make_shared<Registerer>(std::forward<T>(instance));
			_service_registerers.insert(registerer);

			return static_cast<typename Registerer::Type&>(*registerer);
		}

		template<class T>
		auto& registerType()
		{
			using Registerer = Details::ServiceTypeRegisterer<T>;

			auto registerer = std::make_shared<Registerer>();
			_service_registerers.insert(registerer);

			return static_cast<typename Registerer::Type&>(*registerer);
		}

		template<class T>
		auto& registerFactory(T factory)
		{
			using Registerer = Details::ServiceFactoryRegisterer<typename Details::UnderlyingType<decltype(factory())>::Type>;

			auto registerer = std::make_shared<Registerer>(static_cast<std::function<decltype(factory())()>>(factory));
			_service_registerers.insert(registerer);

			return static_cast<typename Registerer::Type&>(*registerer);
		}

		Container build() const
		{
			return Container(getServiceResolvers());
		}

	private:
		std::set<std::shared_ptr<Details::ServiceResolver<>>> getServiceResolvers() const
		{
			std::set<std::shared_ptr<Details::ServiceResolver<>>> result;

			for (const auto& registerer : _service_registerers)
			{
				const auto& resolvers = registerer->getServiceResolvers();
				result.insert(begin(resolvers), end(resolvers));
			}

			return result;
		}

	private:
		std::set<std::shared_ptr<Details::ServiceRegisterer<>>> _service_registerers;
	};

}