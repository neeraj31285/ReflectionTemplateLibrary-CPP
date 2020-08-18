
#include <typeinfo>

#include "FunctorMetaData.h"

namespace rtl {

	template<class _type>
	inline constexpr const unsigned ReflTypeID::get() 
	{
		static const unsigned typeId = m_idCounter++;
		return typeId;
	}

	template<>
	inline const std::string ReflTypeID::toString<void>() {
		return std::string(typeid(void).name());
	}

	template<class _type>
	inline constexpr const std::string ReflTypeID::toString()
	{
		const bool isConst = std::is_const_v<std::remove_reference_t<_type>>;
		const bool isTypeString = std::is_same_v<std::remove_const_t<std::remove_reference_t<_type>>, std::string>;
		const std::string typeStr = isTypeString ? "std::string" : typeid(_type).name();
		if (std::is_lvalue_reference_v<_type>)
		{
			return (isConst ? "const " : "") + typeStr + "&";
		}
		else if (std::is_rvalue_reference_v<_type>)
		{
			return (isConst ? "const " : "") + typeStr + "&&";
		}
		return (isConst ? "const " : "") + typeStr;
	}

	inline FunctorMetaData::FunctorMetaData(const unsigned pMethodId, const unsigned pSignatureId, const unsigned pFunctorIndex,
										    const unsigned pReturnTypeId, const std::string& pReturnStr)
	: m_methodId(pMethodId)
	, m_signatureId(pSignatureId)
	, m_functorIndex(pFunctorIndex)
	, m_returnTypeId(pReturnTypeId)
	, m_returnStr(pReturnStr){ }

	inline FunctorMetaData::FunctorMetaData(const unsigned pMethodId, const unsigned pSignatureId, const unsigned pFunctorIndex,
										    const unsigned pReturnTypeId, const std::string& pReturnStr, const std::vector<std::string>& pSignIdStrs)
	: m_methodId(pMethodId)
	, m_signatureId(pSignatureId)
	, m_functorIndex(pFunctorIndex)
	, m_returnTypeId(pReturnTypeId)
	, m_returnStr(pReturnStr)
	, m_signatureIdStr(pSignIdStrs){ }

	inline const unsigned FunctorMetaData::getFunctorId() const
	{
		return m_methodId;
	}

	inline const unsigned FunctorMetaData::getFunctorIndex() const
	{
		return m_functorIndex;
	}

	inline const unsigned FunctorMetaData::getReturnTypeId() const
	{
		return m_returnTypeId;
	}

	inline const unsigned FunctorMetaData::getSignatureId() const
	{
		return m_signatureId;
	}

	template<class..._args>
	inline void SignatureId<_args...>::buildSignatureId(std::vector<std::string>& pSignIdStrs)
	{

	}

	template<class _arg0, class..._args>
	inline void SignatureId<_arg0, _args...>::buildSignatureId(std::vector<std::string>& pSignIdStrs)
	{
		pSignIdStrs.push_back(ReflTypeID::toString<_arg0>());
		SignatureId<_args...>::buildSignatureId(pSignIdStrs);
	}

	template<class _retTy>
	inline static const FunctorMetaData FunctorMetaData::build(const unsigned pMethodId, const unsigned pSignatureId, const unsigned pFunctorIndex)
	{
		return FunctorMetaData(pMethodId, pSignatureId, pFunctorIndex, ReflTypeID::get<_retTy>(), ReflTypeID::toString<_retTy>());
	}

	template<class _retTy, class _arg0, class..._args>
	inline static const FunctorMetaData FunctorMetaData::build(const unsigned pMethodId, const unsigned pSignatureId, const unsigned pFunctorIndex)
	{
		std::vector<std::string> signatureIdStr;

		SignatureId<_arg0, _args...>::buildSignatureId(signatureIdStr);
		signatureIdStr.shrink_to_fit();

		return FunctorMetaData(pMethodId, pSignatureId,  pFunctorIndex, ReflTypeID::get<_retTy>(), ReflTypeID::toString<_retTy>(), signatureIdStr);
	}
}