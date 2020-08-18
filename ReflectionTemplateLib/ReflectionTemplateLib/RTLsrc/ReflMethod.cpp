#include <cassert>
#include <vector>

#include "ReflMethod.h"
#include "FunctorMetaData.hpp"
#include "MethodReflection.h"
#include "ReflClass.h"
#include "ReflClass.hpp"

using namespace std;

namespace rtl {	

	unsigned ReflTypeID::m_idCounter = 0;
	unsigned ReflMethod::m_instanceCount = 0;
	unsigned MethodIdCreater::m_methodIdCounter = 0;

	ReflMethod::ReflMethod(const FunctorTypeId pFunctorTypeId, const FunctorMetaData& pMetaData)
	: m_functorMetaDataMap{ make_pair(pFunctorTypeId, pMetaData) }
	, m_hasConstOverload(false)
	, m_isAmbiguous(false)
	{
		m_instanceCount++;
	}

	ReflMethod::ReflMethod(const FunctorTypeId pFunctorTypeId, const FunctorMetaData& pMetaData, const bool pIsConstMethod)
	: m_constFunctorMetaDataMap{ make_pair(pFunctorTypeId, pMetaData) }
	, m_hasConstOverload(pIsConstMethod)
	, m_isAmbiguous(false)
	{
		m_instanceCount++;
	}

	void ReflMethod::mergeOverloads(const ReflMethod& pSrcFunction) const
	{
		m_functorMetaDataMap.insert(pSrcFunction.m_functorMetaDataMap.begin(), pSrcFunction.m_functorMetaDataMap.end());
		m_constFunctorMetaDataMap.insert(pSrcFunction.m_constFunctorMetaDataMap.begin(), pSrcFunction.m_constFunctorMetaDataMap.end());
		m_hasConstOverload = !m_constFunctorMetaDataMap.empty();
	}

	void ReflMethod::mergeInheritedOverloads(const ReflMethod& pSrcFunction, const bool pIsAlreadyInherited) const
	{
		vector<FunctorTypeId> failedOverloadIds;
		vector<FunctorTypeId> failedConstOverloadIds;

		for (const auto& itr : pSrcFunction.m_functorMetaDataMap)
		{
			const FunctorTypeId fnctrTypeId = itr.first;
			if (m_functorMetaDataMap.find(fnctrTypeId) == m_functorMetaDataMap.end())
			{
				m_functorMetaDataMap.emplace(itr);
			}
			else failedOverloadIds.push_back(fnctrTypeId);
		}
		for (const auto& itr : pSrcFunction.m_constFunctorMetaDataMap)
		{
			const FunctorTypeId fnctrTypeId = itr.first;
			if (m_constFunctorMetaDataMap.find(fnctrTypeId) == m_constFunctorMetaDataMap.end())
			{
				m_constFunctorMetaDataMap.emplace(itr);
			}
			else failedConstOverloadIds.push_back(fnctrTypeId);
		}

		m_isAmbiguous = false;
		if (pIsAlreadyInherited && !(failedOverloadIds.empty() && failedConstOverloadIds.empty()))
		{
			if (m_ownerReflClass != pSrcFunction.m_ownerReflClass) 
			{
				if (m_ownerReflClass->isCastSafeToTypeId(pSrcFunction.m_ownerReflClass->getReflClassId())) 
				{
					for (const FunctorTypeId fnctorTypeId : failedOverloadIds) 
					{
						m_functorMetaDataMap.at(fnctorTypeId) = pSrcFunction.m_functorMetaDataMap.at(fnctorTypeId);
					}
					for (const FunctorTypeId fnctorTypeId : failedConstOverloadIds)
					{
						m_constFunctorMetaDataMap.at(fnctorTypeId) = pSrcFunction.m_constFunctorMetaDataMap.at(fnctorTypeId);
					}
				}
				else
				{
					m_isAmbiguous = true;
				}
			}
		}
		m_hasConstOverload = !m_constFunctorMetaDataMap.empty();
	}
}