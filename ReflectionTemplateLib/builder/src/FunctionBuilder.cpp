

#include "FunctionBuilder.h"

namespace rtl {

	namespace builder 
	{
		FunctionBuilder<>::FunctionBuilder(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction)
			: m_record(pRecord)
			, m_function(pFunction)
			, m_namespace(pNamespace) {

		}
	}
}