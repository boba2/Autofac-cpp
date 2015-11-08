#pragma once

#include <functional>
#include <memory>
#include "FunctionTraits.h"
#include "../Error/ServiceNotResolvableAs.h"

namespace DI
{
	class Container;

	namespace Details
	{

		struct FactoryUnifier
		{
			template<class S>
			static auto unifyFactory(S factory)
			{
				return Impl<S, std::make_index_sequence<FunctionArity<S>::value>>::unify(factory);
			}

			template<class S, class>
			struct Impl;

			template<class S, size_t... I>
			struct Impl<S, std::index_sequence<I...>>
			{
				static auto unify(S factory)
				{
					return [factory](Container* container) { auto resolver = ArgumentResolver(container); return factory(wrapValue<I>(resolver)...); };
				}
			};

			struct ArgumentResolver
			{
				explicit ArgumentResolver(Container* container)
					: _container(container)
				{}

				template<class U>
				operator U()
				{
					return _container->resolve<U>();
				}

				template<class U>
				operator U&() const
				{
					return _container->resolve<U&>();
				}

				Container* _container;
			};

			template<int>
			static ArgumentResolver& wrapValue(ArgumentResolver& object)
			{
				return object;
			}
		};

		template<class T>
		struct FactoryRunner
		{
			using FactoryType = std::function<T(Container*)>;

			explicit FactoryRunner(FactoryType factory)
				: _factory(factory)
			{}

			T* createPtr(Container*) const
			{
				throw Error::ServiceNotResolvableAs();
			}

			std::shared_ptr<T> createSharedPtr(Container* container) const
			{
				return std::make_shared<T>(_factory(container));
			}

			std::unique_ptr<T> createUniquePtr(Container* container) const
			{
				return std::make_unique<T>(_factory(container));
			}

			FactoryType _factory;
		};

		template<class T>
		struct FactoryRunner<T*>
		{
			using FactoryType = std::function<T*(Container*)>;

			explicit FactoryRunner(FactoryType factory)
				: _factory(factory)
			{}

			T* createPtr(Container* container) const
			{
				return _factory(container);
			}

			std::shared_ptr<T> createSharedPtr(Container* container) const
			{
				return std::shared_ptr<T>(_factory(container), NullDeleter());
			}

			std::unique_ptr<T> createUniquePtr(Container*) const
			{
				throw Error::ServiceNotResolvableAs();
			}

			struct NullDeleter
			{
				void operator()(T*) const {}
			};

			FactoryType _factory;
		};

		template<class T>
		struct FactoryRunner<std::shared_ptr<T>>
		{
			using FactoryType = std::function<std::shared_ptr<T>(Container*)>;

			explicit FactoryRunner(FactoryType factory)
				: _factory(factory)
			{}

			T* createPtr(Container*) const
			{
				throw Error::ServiceNotResolvableAs();
			}

			std::shared_ptr<T> createSharedPtr(Container* container) const
			{
				return _factory(container);
			}

			std::unique_ptr<T> createUniquePtr(Container*) const
			{
				throw Error::ServiceNotResolvableAs();
			}

			FactoryType _factory;
		};

		template<class T>
		struct FactoryRunner<std::unique_ptr<T>>
		{
			using FactoryType = std::function<std::unique_ptr<T>(Container*)>;

			explicit FactoryRunner(FactoryType factory)
				: _factory(factory)
			{}

			T* createPtr(Container*) const
			{
				throw Error::ServiceNotResolvableAs();
			}

			std::shared_ptr<T> createSharedPtr(Container* container) const
			{
				return std::shared_ptr<T>(_factory(container));
			}

			std::unique_ptr<T> createUniquePtr(Container* container) const
			{
				return _factory(container);
			}

			FactoryType _factory;
		};

	}
}