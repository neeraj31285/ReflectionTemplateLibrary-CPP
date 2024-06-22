#include "CxxMirrorBuilder.h"

namespace rtl 
{
	namespace builder 
	{
		Reflect::Reflect()
			: m_record("")
			, m_namespace("")
		{
		}

		Reflect& Reflect::record(const std::string& pClass)
		{
			m_record = pClass;
			return *this;
		}

		Reflect& Reflect::nameSpace(const std::string& pNamespace/* = NAMESPACE_GLOBAL*/)
		{
			m_namespace = pNamespace;
			return *this;
		}

		const FunctionBuilder Reflect::function(const std::string& pFunction)
		{
			return FunctionBuilder(m_namespace, m_record, pFunction);
		}
	}
}