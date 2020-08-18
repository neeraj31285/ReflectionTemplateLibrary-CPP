#pragma once

#include <map>
#include <functional>
#include <unordered_map>

#include "ReflObject.h"
#include "ReflExecuter.h"
#include "TypeConstants.h"

namespace rtl {
	
	class ReflClass;
	class FunctorMetaData;

	class ReflMethod 
	{
		static ReflMethodId m_instanceCount;

		mutable bool m_isAmbiguous;
		mutable bool m_hasConstOverload;
		mutable const ReflClass* m_ownerReflClass;
		mutable FunctorMetaDataMap m_functorMetaDataMap;
		mutable FunctorMetaDataMap m_constFunctorMetaDataMap;

		void setOwnerClass(const ReflClass& pOwnerClass) const;
		void mergeOverloads(const ReflMethod& pSrcFunction) const;
		void mergeInheritedOverloads(const ReflMethod& pSrcFunction, const bool pIsOwnerOtherBase) const;

		ReflMethod(const FunctorTypeId pFunctorTypeId, const FunctorMetaData& pMetaData);
		ReflMethod(const FunctorTypeId pFunctorTypeId, const FunctorMetaData& pMetaData, const bool pIsConstMethod);

	public: friend ReflClass;

		ReflMethod() = delete;

		const bool isAmbiguous() const;
		const bool hasConstOverload() const;
		const FunctorMetaDataMap& getFunctorTypeIdIndexMap() const;
		const FunctorMetaDataMap& getConstFunctorTypeIdIndexMap() const;

		template<class _retTy, class..._args>
		const bool isSignature() const;

		template<class _retTy>
		const bool isReturnType() const;

		template<class _classTy, class _retTy, class... _args>
		static const ReflMethod init(_retTy(_classTy::* pFunctor)(_args...));

		template<class _classTy, class _retTy, class... _args>
		static const ReflMethod init(_retTy(_classTy::* pFunctor)(_args...) const);

		template<class _objTy>
		const ReflExecuter<typeQ::MUTABLE> operator()(const ReflObject<_objTy>& pTargetReflObj) const;

		template<class _objTy>
		const ReflExecuter<typeQ::CONST> operator()(const ReflObject<const _objTy>& pTargetReflObj) const;
	};
}