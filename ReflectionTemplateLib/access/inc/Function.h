#pragma once

#include <string>
#include <memory>
#include <vector>

#include "Constants.h"

namespace rtl {

	using signatureId = std::size_t;
	using functorIndex = std::size_t;

	namespace builder 
	{
		class FunctionBuilder;
	}

	namespace access
	{
		class Record;
		class RObject;
		class NameSpace;
		class MethodInvoker;

		class Function
		{
			friend Record;
			friend NameSpace;
			friend MethodInvoker;
			friend builder::FunctionBuilder;

			const std::string m_record;
			const std::string m_function;
			const std::string m_namespace;

			mutable std::string m_signatures;
			mutable std::vector<std::pair<signatureId, functorIndex>> m_functorHash;

			void sortFunctorsHash() const;
			
			void addOverload(const Function& pOtherFunc) const;

			const bool hasSignatureId(const signatureId pSignId, std::pair<signatureId, functorIndex>& pFuncHash) const;

			Function(const std::string& pNamespace, const std::string& pClassName, const std::string& pFuncName,
				 const std::string& pSignature, const std::size_t& pSignatureId, const std::size_t& pFunctorId);

			template<class ..._args>
			std::unique_ptr<RObject> operator()(const std::unique_ptr<RObject>& pTarget, _args...params) const;

		public: 
			
			Function() = delete;

			GETTER(std::string, RecordName, m_record)
			GETTER(std::string, FunctionName, m_function)
			GETTER(std::string, Signatures, m_signatures)
			GETTER(std::string, Namespace, m_namespace)

			template<class _arg0, class ..._args>
			const bool hasSignature() const;

			template<class ..._args>
			std::unique_ptr<RObject> operator()(_args...params) const noexcept;
		};
	}
}