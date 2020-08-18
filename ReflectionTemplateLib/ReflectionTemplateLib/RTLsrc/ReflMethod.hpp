#pragma once

#include <cassert>
#include <iostream>

#include "CppMirror.h"
#include "ReflMethod.h"
#include "FunctorMetaData.hpp"
#include "MethodReflection.h"

namespace rtl 
{
	inline const bool ReflMethod::isAmbiguous() const
	{
		return m_isAmbiguous;
	}
	inline const bool ReflMethod::hasConstOverload() const
	{
		return m_hasConstOverload;
	}

	inline void ReflMethod::setOwnerClass(const ReflClass& pOwnerClass) const
	{
		m_ownerReflClass = &pOwnerClass;
	}

	inline const FunctorMetaDataMap& ReflMethod::getFunctorTypeIdIndexMap() const
	{
		return m_functorMetaDataMap;
	}

	inline const FunctorMetaDataMap& ReflMethod::getConstFunctorTypeIdIndexMap() const
	{
		return m_constFunctorMetaDataMap;
	}

	template<class _objTy>
	inline const ReflExecuter<typeQ::MUTABLE> ReflMethod::operator()(const ReflObject<_objTy>& pTargetReflObj) const
	{
		if (m_isAmbiguous)
		{
			std::cout << "\n\n[warning]..\t\t\t{ Ambiguous function, calling::" << m_ownerReflClass->getClassName() << "() }";
		}
		const bool isTypeSafe = m_ownerReflClass->isCastSafeToTypeId(pTargetReflObj.getTypeId());
		assert(isTypeSafe && "Object & method type mismatch. Bad function call exception.. abort!");
		return ReflExecuter<typeQ::MUTABLE>(*this, pTargetReflObj.getTypeId(), static_cast<void*>(pTargetReflObj.get()));
	}

	template<class _objTy>
	inline const ReflExecuter<typeQ::CONST> ReflMethod::operator()(const ReflObject<const _objTy>& pTargetReflObj) const
	{
		if (m_isAmbiguous)
		{
			std::cout << "\n[WARNING]..\t\t\t{ Ambiguous function, calling::" << m_ownerReflClass->getClassName() << "() }\n";
		}
		const bool isTypeSafe = m_ownerReflClass->isCastSafeToTypeId(pTargetReflObj.getTypeId()); 
		assert(isTypeSafe && "Object & method type mismatch. Bad function call exception.. abort!");
		return ReflExecuter<typeQ::CONST>(*this, pTargetReflObj.getTypeId(), static_cast<const void*>(pTargetReflObj.get()));
	}

	template<class _classTy, class _retTy, class... _args>
	inline const ReflMethod ReflMethod::init(_retTy(_classTy::*pFunctor)(_args...))
	{
		const auto functor = [=](const unsigned pTargetTypeId, void* pTarget, _args... params)->_retTy
		{
			if (ClassReflection<_classTy>::isReflTypeIdSame(pTargetTypeId)) 
			{
				return	((static_cast<_classTy*>(pTarget))->*pFunctor)(params...);
			}
			else
			{
				const InheritanceCastFunctor safeUp_cast = ClassReflection<_classTy>::getSafeUpCastFptr(pTargetTypeId);
				return	((static_cast<_classTy*>(safeUp_cast(pTarget, pTargetTypeId)))->*pFunctor)(params...);
			}
		};
		const unsigned functorIndex = MethodReflection<_retTy, _args...>::addLambdaWrappedFunctor<typeQ::MUTABLE>(m_instanceCount, functor);
		const FunctorMetaData mthdMetaData = FunctorMetaData::build<_retTy, _args...>(m_instanceCount, FunctorSignature<_args...>::TypeId, functorIndex);

		return ReflMethod(MethodReflection<_retTy, _args...>::TypeId, mthdMetaData);
	}

	template<class _classTy, class _retTy, class... _args>
	inline const ReflMethod ReflMethod::init(_retTy(_classTy::* pFunctor)(_args...) const)
	{
		const auto functor = [=](const unsigned pTargetTypeId, const void* pTarget, _args... params)->_retTy
		{
			if (ClassReflection<_classTy>::isReflTypeIdSame(pTargetTypeId))
			{
				return	((static_cast<const _classTy*>(pTarget))->*pFunctor)(params...);
			}
			else
			{
				const InheritanceCastFunctor safeUp_cast = ClassReflection<_classTy>::getSafeUpCastFptr(pTargetTypeId);
				return	((static_cast<const _classTy*>(safeUp_cast(const_cast<void*>(pTarget), pTargetTypeId)))->*pFunctor)(params...);
			}
		};
		
		const unsigned functorIndex = MethodReflection<_retTy, _args...>::addLambdaWrappedFunctor<typeQ::CONST>(m_instanceCount, functor);
		const FunctorMetaData mthdMetaData = FunctorMetaData::build<_retTy, _args...>(m_instanceCount, FunctorSignature<_args...>::TypeId, functorIndex);

		return ReflMethod(MethodReflection<_retTy, _args...>::TypeId, mthdMetaData, true);
	}

	template<class _retTy, class..._args>
	inline const bool ReflMethod::isSignature() const
	{
		const unsigned methodId = MethodReflection<_retTy, _args...>::TypeId;
		if (m_functorMetaDataMap.find(methodId) == m_functorMetaDataMap.end() && 
			m_constFunctorMetaDataMap.find(methodId) == m_constFunctorMetaDataMap.end())
		{
			return false;
		}
		return true;
	}

	template<class _retTy>
	inline const bool ReflMethod::isReturnType() const
	{
		const unsigned returnId = ReflTypeID::get<_retTy>();
		for (const auto& itr : m_functorMetaDataMap)
		{
			if (itr.second.getReturnTypeId() == returnId)
			{
				return true;
			}
		}
		for (const auto& itr : m_constFunctorMetaDataMap)
		{
			if (itr.second.getReturnTypeId() == returnId)
			{
				return true;
			}
		}
		return false;
	}
}






//const InheritanceCastFunctor safeUp_cast = ClassReflection<_classTy>::getSafeDowncastFptr(pTargetTypeId);
//std::cout << std::endl; 
//void* const target = safeUp_cast(pTarget, pTargetTypeId);
//std::cout << "\n[FINL_cast]..\t\t\t{ sc<" << typeid(_classTy).name() << ">(" << pTargetTypeId << ") }\n";
//return	((static_cast<_classTy*>(target))->*pFunctor)(params...);
