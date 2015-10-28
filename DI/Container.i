#pragma once

#include "Container.h"
#include "Details/UnderlyingType.h"

namespace DI
{

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