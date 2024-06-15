#include "CxxMirrorBuilder.h"

namespace rtl 
{
	Reflect::Reflect()
	: m_class("")
	, m_function("")
	, m_namespace("")
	{
	}

	Reflect& Reflect::record(const std::string& pClass)
	{
		m_class = pClass;
		return *this;
	}

	const Reflect& Reflect::function(const std::string& pFunction)
	{
		m_function = pFunction;
		return *this;
	}

	Reflect& Reflect::nameSpace(const std::string& pNamespace/* = NS_GLOBAL*/)
	{
		m_namespace = pNamespace;
		return *this;
	}
}