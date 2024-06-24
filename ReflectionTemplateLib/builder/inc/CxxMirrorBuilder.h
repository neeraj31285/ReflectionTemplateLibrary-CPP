#pragma once

#include "Constants.h"
#include "NameSpace.h"
#include "FunctionBuilder.hpp"
#include "ConstructorBuilder.hpp"

namespace rtl {

	namespace builder 
	{
		// Builder class to encapsulate all type names, pointers.
		class Reflect
		{
			std::string m_record;
			std::string m_namespace;

		public:

			Reflect();
			Reflect(const Reflect&) = delete;
			Reflect& operator=(const Reflect&) = delete;

			Reflect& record(const std::string& pClass);

			Reflect& nameSpace(const std::string& pNamespace);

			const FunctionBuilder function(const std::string& pFunction);

			template<class _recordType>
			const ConstructorBuilder<_recordType> constructor()
			{
				return ConstructorBuilder<_recordType>(m_namespace, m_record);
			}
		};
	}
}