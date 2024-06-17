#pragma once

#include <vector>
#include <iostream>
#include <functional>


namespace rtl {

	template<class _signListA, class _signListB>
	using enable_if_sign_same = typename std::enable_if< std::is_same<_signListA, _signListB>::value >::type;

	template<class _signListA, class _signListB>
	using enable_if_sign_diff = typename std::enable_if< !std::is_same<_signListA, _signListB>::value >::type;

	template<class ..._signature>
	class FunctorContainer
	{
		static const std::size_t m_containerId;

		static std::vector<std::function<void(_signature...)>> m_functors;

	public:

		static const std::size_t& getContainerId();

		template<class ..._params>
		static void dispatchCall(std::size_t pFunctorId, _params..._args);

		template<class _returnType>
		static int addFunctor(_returnType(*pFunctor)(_signature...));

		template<class _recordType>
		static int addConstructor();

		template<class _signListA, class _signListB, class ..._params>
		static void resolveCall(std::size_t pFunctorId, enable_if_sign_same<_signListA, _signListB> *_, _params..._args);

		template<class _signListA, class _signListB, class ..._params>
		static void resolveCall(std::size_t pFunctorId, enable_if_sign_diff<_signListA, _signListB> *_, _params..._args);
	};
}
