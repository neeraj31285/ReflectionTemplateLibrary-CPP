#pragma once

#include <vector>
#include <functional>

#include "Constants.h"

namespace rtl {

	namespace access {
		class Rany;
		class Function;
	}

	namespace builder {
		template<class ..._args>
		class FunctionBuilder;
	}

	namespace detail
	{
		template<class ..._signature>
		class FunctorContainer
		{
			friend access::Function;

			template<class ..._args>
			friend class builder::FunctionBuilder;

		public:

			static const std::size_t& getContainerId();

		private: 
			
			static const std::size_t m_containerId;

			using FunctorType = std::function < access::Rany(_signature...) >;
			using MethodPtrType = std::function < access::Rany(const access::Rany&, _signature...) >;

			static std::vector<FunctorType> m_functors;
			static std::vector<MethodPtrType> m_methodPtrs;

			template<class _recordType>
			static int addConstructor();

			template<class _returnType>
			static int addFunctor(_returnType(*pFunctor)(_signature...), enable_if_same<_returnType, void> *_ = nullptr);

			template<class _returnType>
			static int addFunctor(_returnType(*pFunctor)(_signature...), enable_if_notSame<_returnType, void> *_ = nullptr);

			template<class _recordType, class _returnType>
			static int addFunctor(_returnType(_recordType::* pFunctor)(_signature...), enable_if_same<_returnType, void> *_ = nullptr);

			template<class _recordType, class _returnType>
			static int addFunctor(_returnType(_recordType::* pFunctor)(_signature...), enable_if_notSame<_returnType, void> *_ = nullptr);

			template<class ..._params>
			static access::Rany reflectCall(std::size_t pFunctorId, _params..._args);

			template<class ..._params>
			static access::Rany reflectCall(const access::Rany& pTarget, std::size_t pFunctorId, _params..._args);
		};
	}
}