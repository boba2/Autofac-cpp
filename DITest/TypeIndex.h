#pragma once

#include <typeindex>
#include "UnderlyingType.h"

template<class T>
struct TypeIndex : std::type_index
{
	TypeIndex()
		: type_index(typeid(UnderlyingType<T>::Type))
	{}
};
