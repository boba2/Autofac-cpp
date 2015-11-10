#pragma once

#include "../Support/DIdecl.h"
#include "ServiceResolverCreator.h"

namespace DI
{
	namespace Details
	{

		class DI_API ServiceResolvers
		{
		public:
			ServiceResolvers();
			ServiceResolvers(ServiceResolvers&& other);
			~ServiceResolvers();

			void add(ServiceResolverCreatorPtr resolver);
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