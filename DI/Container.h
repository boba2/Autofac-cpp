#pragma once

#include "Support/DIdecl.h"
#include "Details/ServiceReferenceTypeConverter.h"
#include "Details/UnderlyingType.h"
#include "Details/CompositeServiceResolver.h"
#include "Details/TypeIndex.h"

namespace DI
{

	namespace Details
	{
		class ServiceResolvers;
	}

	class DI_API Container
	{
	public:
		Container();
		Container(const Container& other);
		Container& operator=(const Container& other);

		template<class T>
		auto resolve() -> typename Details::ServiceReferenceTypeConverter<T>::Result;

	private:
		class Impl;

		explicit Container(Details::ServiceResolvers service_resolvers);
		explicit Container(std::shared_ptr<Impl> impl);

		template<class T>
		auto& getResolver() const;

		auto getResolver(const Details::TypeIndex& type_index) const -> Details::CompositeServiceResolver<>&;

		friend class ContainerBuilder;

	private:
#pragma warning(disable:4251)
		std::shared_ptr<Impl> _impl;
#pragma warning(default:4251)
	};

	template<class T>
	auto Container::resolve() -> typename Details::ServiceReferenceTypeConverter<T>::Result
	{
		using ServiceReferenceTypeConverter = Details::ServiceReferenceTypeConverter<T>;

		return ServiceReferenceTypeConverter::convertFrom(getResolver<T>(), this);
	}

	template<class T>
	auto& Container::getResolver() const
	{
		using ServiceType = typename Details::UnderlyingType<T>::Type;
		using ServiceResolverType = Details::CompositeServiceResolver<ServiceType>;

		return dynamic_cast<ServiceResolverType&>(getResolver(Details::TypeIndex::from<ServiceType>()));
	}

}