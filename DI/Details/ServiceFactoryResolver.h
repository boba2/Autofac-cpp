#pragma once

#include "ServiceResolver.h"
#include "FactoryRunner.h"

namespace DI
{
	namespace Details
	{

		template<class T, class FactoryType = T, class FactoryResultType = typename FunctionResultType<FactoryType>::Type, class ResultType = typename UnderlyingType<FactoryResultType>::Type>
		class ServiceFactoryResolver : public ServiceResolver<ResultType>
		{
			using ServiceType = typename ServiceResolver<ResultType>::ServiceType;
			using ServiceRefType = typename ServiceResolver<ResultType>::ServiceRefType;
			using ServicePtrType = typename ServiceResolver<ResultType>::ServicePtrType;
			using ServiceSharedPtrType = typename ServiceResolver<ResultType>::ServiceSharedPtrType;
			using ServiceUniquePtrType = typename ServiceResolver<ResultType>::ServiceUniquePtrType;

		public:
			explicit ServiceFactoryResolver(FactoryType factory)
				: _factory_runner(FactoryUnifier::unifyFactory(factory))
			{}

		private:
			virtual ServiceType getService(Container* container) override
			{
				return *_factory_runner.createSharedPtr(container).get();
			}

			virtual ServiceRefType getServiceAsRef(Container* container) override
			{
				return *_factory_runner.createPtr(container);
			}

			virtual ServicePtrType getServiceAsPtr(Container* container) override
			{
				return _factory_runner.createPtr(container);
			}

			virtual ServiceSharedPtrType getServiceAsSharedPtr(Container* container) override
			{
				return _factory_runner.createSharedPtr(container);
			}

			virtual ServiceUniquePtrType getServiceAsUniquePtr(Container* container) override
			{
				return _factory_runner.createUniquePtr(container);
			}

			FactoryRunner<FactoryResultType> _factory_runner;
		};

	}
}