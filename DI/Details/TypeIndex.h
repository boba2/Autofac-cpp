#pragma once

#include <typeindex>

namespace DI
{
	namespace Details
	{

		struct TypeIndex : std::type_index
		{
			template<class T>
			static TypeIndex from()
			{
				return TypeIndex(typeid(T));
			}

		protected:
			explicit TypeIndex(const std::type_info& type_info)
				: type_index(type_info)
			{}
		};

	}
}

namespace std
{
	template<>
	struct hash<DI::Details::TypeIndex>
	{
		size_t operator()(const DI::Details::TypeIndex& index) const
		{
			return std::hash<type_index>()(static_cast<const type_index&>(index));
		}
	};
}
