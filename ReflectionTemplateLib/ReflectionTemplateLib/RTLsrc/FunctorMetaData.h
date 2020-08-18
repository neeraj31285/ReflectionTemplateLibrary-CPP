#pragma once

#include "TypeConstants.h"

namespace rtl {

	class ReflTypeID
	{
		static unsigned m_idCounter;

	public:

		template<class _type>
		static constexpr const unsigned get();

		template<class _type>
		static constexpr const std::string toString();

		template<>
		static const std::string toString<void>();
	};

	template<class..._args>
	struct SignatureId
	{
		static void buildSignatureId(std::vector<std::string>& pSignIdStrs);
	};

	template<class _arg0, class..._args>
	struct SignatureId<_arg0, _args...>
	{
		static void buildSignatureId(std::vector<std::string>& pSignIdStrs);
	};

	class FunctorMetaData
	{
		unsigned m_methodId;
		unsigned m_signatureId;
		unsigned m_functorIndex;
		unsigned m_returnTypeId;
		std::string m_returnStr;
		std::vector<std::string> m_signatureIdStr;

		FunctorMetaData() = delete;

		FunctorMetaData(const unsigned pMethodId, const unsigned pSignatureId, const unsigned pFunctorIndex,
					    const unsigned pReturnTypeId, const std::string& pReturnStr);

		FunctorMetaData(const unsigned pMethodId, const unsigned pSignatureId, const unsigned pFunctorIndex,
						const unsigned pReturnTypeId, const std::string& pReturnStr, const std::vector<std::string>& pSignIdStrs);
	public:

		template<class _retTy>
		static const FunctorMetaData build(const unsigned pMethodId, const unsigned pSignatureId, const unsigned pFunctorIndex);

		template<class _retTy, class _arg0, class..._args>
		static const FunctorMetaData build(const unsigned pMethodId, const unsigned pSignatureId, const unsigned pFunctorIndex);

		const unsigned getFunctorId() const;
		const unsigned getFunctorIndex() const;
		const unsigned getReturnTypeId() const;
		const unsigned getSignatureId() const;
	};
}
