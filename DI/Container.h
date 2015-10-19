#pragma once

#include "Support/DIdecl.h"
#include <set>
#include "Details/ServiceReferenceTypeConverter.h"
#include "Details/ServiceResolver.h"

namespace DI 
{

	class DI_API Container
	{
	public:
		Container();
		Container(const Container& other);
		~Container();
		Container& operator=(const Container& other);

		template<class T>
		auto resolve() -> typename Details::ServiceReferenceTypeConverter<T>::Result
		{
			using ServiceReferenceTypeConverter = Details::ServiceReferenceTypeConverter<T>;
			using ServiceResolverType = Details::ServiceResolver<typename Details::UnderlyingType<T>::Type>;
			using TypeIndex = Details::TypeIndex<T>;

			return ServiceReferenceTypeConverter::convertFrom(dynamic_cast<ServiceResolverType&>(getResolver(TypeIndex())));
		}

	private:
		explicit Container(const std::set<std::shared_ptr<Details::ServiceResolver<>>>& service_resolvers);
		friend class ContainerBuilder;

		Details::ServiceResolver<> &getResolver(const Details::TypeIndex<>& type_index) const;

	private:
		class Impl;
#pragma warning(disable:4251)
		std::shared_ptr<Impl> _impl;
#pragma warning(default:4251)
	};

}