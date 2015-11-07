#pragma once

#include "../Support/DIdecl.h"
#include "ServiceResolver.h"

namespace DI
{
	namespace Details
	{
		
		class DI_API ServiceResolvers
		{
		public:
			ServiceResolvers();
			ServiceResolvers(ServiceResolvers&& other);
			ServiceResolvers(std::initializer_list<std::shared_ptr<ServiceResolver<>>> resolvers);
			~ServiceResolvers();

			void add(std::shared_ptr<ServiceResolver<>> resolver);
			void merge(const ServiceResolvers& other);

			auto empty() const -> bool;
			auto get(TypeIndex<> type_index) const -> std::shared_ptr<ServiceResolver<>>;

		private:
			class Impl;

#pragma warning(disable:4251)
			std::unique_ptr<Impl> _impl;
#pragma warning(default:4251)
		};

	}
}