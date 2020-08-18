#pragma once

#include <cassert>
#include <iostream>

#include "MethodReflection.h"

namespace rtl {

	template<class..._args>
	const unsigned FunctorSignature<_args...>::TypeId = MethodIdCreater::m_methodIdCounter++;

	template<class _retTy, class... _args>
	const unsigned MethodReflection<_retTy, _args...>::TypeId = MethodIdCreater::m_methodIdCounter++;

	template<class _retTy, class... _args>
	std::vector< std::pair< ReflMethodId, std::function<_retTy(const unsigned, void*, _args...)>>> MethodReflection< _retTy, _args...>::m_functors;

	template<class _retTy, class... _args>
	std::vector< std::pair< ReflMethodId, std::function<_retTy(const unsigned, const void*, _args...)>>> MethodReflection< _retTy, _args...>::m_constFunctors;

	template<class _retTy, class... _args>
	template<typeQ _funcTy, class _lambdaTy>
	inline const unsigned MethodReflection< _retTy, _args...>::addLambdaWrappedFunctor(const ReflMethodId pReflMethodId, _lambdaTy pFunctor,
											   sfinae_typeQT<_funcTy, typeQ::CONST>* p_null)
	{
		m_constFunctors.push_back(std::make_pair(pReflMethodId, pFunctor));
		return static_cast<unsigned>(m_constFunctors.size() - 1);
	}

	template<class _retTy, class... _args>
	template<typeQ _funcTy, class _lambdaTy>
	inline const unsigned MethodReflection< _retTy, _args...>::addLambdaWrappedFunctor(const ReflMethodId pReflMethodId, _lambdaTy pFunctor,
											   sfinae_typeQT<_funcTy, typeQ::MUTABLE>* p_null)
	{
		m_functors.push_back(std::make_pair(pReflMethodId, pFunctor));
		return static_cast<unsigned>(m_functors.size() - 1);
	}

	template<class _retTy, class... _args>
	inline _retTy MethodReflection< _retTy, _args...>::execute(const FunctorMetaData& pMethodMeta, const unsigned pTargetTypeId, void* pTarget, _args... params)
	{
		assert(pMethodMeta.getFunctorIndex() < m_functors.size() && "Bad function call exception.. abort!");
		auto& functorPair = m_functors.at(pMethodMeta.getFunctorIndex());
		assert(pMethodMeta.getFunctorId() == functorPair.first && "Bad function call exception.. abort!");
		return (functorPair.second)(pTargetTypeId, pTarget, params...);
	}

	template<class _retTy, class... _args>
	inline _retTy MethodReflection< _retTy, _args...>::execute(const FunctorMetaData& pMethodMeta, const unsigned pTargetTypeId, const void* pTarget, _args... params)
	{
		assert(pMethodMeta.getFunctorIndex() < m_constFunctors.size() && "Bad function call exception.. abort!");
		auto& functorPair = m_constFunctors.at(pMethodMeta.getFunctorIndex());
		assert(pMethodMeta.getFunctorId() == functorPair.first && "Bad function call exception.. abort!");
		return (functorPair.second)(pTargetTypeId, pTarget, params...);
	}
}
