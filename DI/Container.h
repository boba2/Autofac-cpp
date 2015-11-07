#pragma once

#include "Support/DIdecl.h"
#include "Details/ServiceReferenceTypeConverter.h"
#include "Details/ServiceResolver.h"
#include "Details/ServiceResolvers.h"
#include "Details/UnderlyingType.h"

namespace DI
{

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

		auto getResolver(const Details::TypeIndex<>& type_index) const -> Details::ServiceResolver<>&;

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
		using ServiceResolverType = Details::ServiceResolver<ServiceType>;
		using TypeIndex = Details::TypeIndex<ServiceType>;

		return dynamic_cast<ServiceResolverType&>(getResolver(TypeIndex()));
	}

}