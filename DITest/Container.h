#pragma once

#include "Details/ServiceReferenceTypeConverter.h"
#include "Details/ServiceResolver.h"

namespace DI 
{

	class Container
	{
	public:
		virtual ~Container() {}

		template<class T>
		T resolve()
		{
			using ServiceReferenceTypeConverter = Details::ServiceReferenceTypeConverter<T>;

			return ServiceReferenceTypeConverter::convertFrom(getResolver<T>());
		}

	protected:
		virtual Details::ServiceResolver<> &getResolver(const Details::TypeIndex<>& type_index) const = 0;

	private:
		template<class T>
		auto& getResolver() const
		{
			using ServiceResolverType = Details::ServiceResolver<typename Details::UnderlyingType<T>::Type>;
			using TypeIndex = Details::TypeIndex<T>;

			return dynamic_cast<ServiceResolverType&>(getResolver(TypeIndex()));
		}
	};

}