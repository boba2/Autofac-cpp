#pragma once

#include "../Support/DIdecl.h"
#include "ServiceResolver.h"
#include <tuple>
#include "TypeIndex.h"

namespace DI
{
	namespace Details
	{

		using ServiceResolverData = std::tuple<TypeIndex, ServiceResolverPtr<>>;
		
		class DI_API ServiceResolvers
		{
		public:
			ServiceResolvers();
			ServiceResolvers(ServiceResolvers&& other);
			~ServiceResolvers();

			void add(const ServiceResolverData& resolver);
			void merge(const ServiceResolvers& other);

			auto empty() const -> bool;
			auto get(const TypeIndex& type_index) const -> ServiceResolverPtr<>;

		private:
			class Impl;

#pragma warning(disable:4251)
			std::unique_ptr<Impl> _impl;
#pragma warning(default:4251)
		};

	}
}