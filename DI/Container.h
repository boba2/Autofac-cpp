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
		auto resolve() -> typename Details::ServiceReferenceTypeConverter<T>::Result;

	private:
		class Impl;

		explicit Container(const std::set<std::shared_ptr<Details::ServiceResolver<>>>& service_resolvers);
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

}

#include "Container.i"