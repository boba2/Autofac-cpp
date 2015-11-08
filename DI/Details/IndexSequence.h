#pragma once

namespace DI
{
	namespace Details
	{
		
		template<size_t...>
		struct IndexSequence {};

		template<size_t N, size_t... I>
		struct MakeIndexSequenceImpl : MakeIndexSequenceImpl<N - 1, N, I...>
		{};

		template<size_t... I>
		struct MakeIndexSequenceImpl<0, I...>
		{
			using Type = IndexSequence<I...>;
		};

		template<size_t N>
		using MakeIndexSequence = typename MakeIndexSequenceImpl<N>::Type;

	}
}