#pragma once

#include "TypeList.h"
#include "Function.h"
#include "Constants.h"
#include "FunctorContainer.hpp"

namespace rtl {
	
	template<class ..._args>
	inline std::unique_ptr<RObject> Function::execute(_args ...params) const
	{
		if (!m_isMemberFunction && m_signatureId == FunctorContainer<_args...>::getContainerId()) {
			return FunctorContainer<_args...>::reflectCall(m_functorId, params...);
		}
		else {
			assert(false && "Throw bad call exception");
		}
		return nullptr;
	}


	template<typename _recordType, class ..._ctorSignature>
	inline const Function Function::addConstructor(const std::string& pNamespace, const std::string& pRecord)
	{
		const auto& namspaceStr = (pNamespace != NS_GLOBAL) ? pNamespace : "";
		const auto& recordTypeStr = namspaceStr + "::" + pRecord;

		const std::size_t signatureId = FunctorContainer<_ctorSignature...>::getContainerId();
		const std::size_t functorId = FunctorContainer<_ctorSignature...>::template addConstructor<_recordType>(recordTypeStr);
		const std::string& ctorName = (pRecord + CTOR_SUFFIX + std::to_string(signatureId));
		const std::string& signature = "(" + TypeList<_ctorSignature...>::toString() + ")";
		return Function(pNamespace, pRecord, ctorName, signature, signatureId, functorId, false);
	}


	template<class _returnType, class ..._signature>
	inline const Function Function::addFunctor(const std::string& pNamespace, const std::string& pClassName,
						   const std::string& pFunctionName, _returnType(*pFunctor)(_signature...))
	{
		const std::size_t signatureId = FunctorContainer<_signature...>::getContainerId();
		const std::size_t functorId = FunctorContainer<_signature...>::addFunctor(pFunctor);
		const std::string& signature = "(" + TypeList<_signature...>::toString() + ")";
		return Function(pNamespace, pClassName, pFunctionName, signature, signatureId, functorId, false);
	}

	template<class _recordType, class _returnType, class ..._signature>
	inline const Function Function::addFunctor(const std::string& pNamespace, const std::string& pClassName,
						   const std::string& pFunctionName, _returnType(_recordType::* pFunctor)(_signature...))
	{
		const std::size_t signatureId = FunctorContainer<_signature...>::getContainerId();
		const std::size_t functorId = FunctorContainer<_signature...>::addFunctor(pFunctor);
		const std::string& signature = "(" + TypeList<_signature...>::toString() + ")";
		return Function(pNamespace, pClassName, pFunctionName, signature, signatureId, functorId, true);
	}
}