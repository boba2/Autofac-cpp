#pragma once

namespace DI
{
	namespace Details
	{
		
		template<int...>
		struct IndexSequence {};

		template<int N, int... I>
		struct MakeIndexSequenceImpl : MakeIndexSequenceImpl<N - 1, N, I...>
		{};

		template<int... I>
		struct MakeIndexSequenceImpl<0, I...>
		{
			using Type = IndexSequence<I...>;
		};

		template<int N>
		using MakeIndexSequence = typename MakeIndexSequenceImpl<N>::Type;

	}
}