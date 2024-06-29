
#include <cassert>

#include "Record.h"
#include "Function.h"
#include "Constants.h"
#include "FunctorContainer.hpp"

namespace rtl {

	namespace access 
	{
		template<class ..._ctorArgs>
		inline Rany Record::newInstance(_ctorArgs ...params) const
		{
			const auto& ctorName = (m_recordName + CTOR_SUFFIX);
			const auto& itr = m_functions.find(ctorName);
			if (itr != m_functions.end()) {
				return itr->second(params...);
			}
			else {
				assert(false && "Throw bad call exception");
			}
			return Rany();
		}
	}
}