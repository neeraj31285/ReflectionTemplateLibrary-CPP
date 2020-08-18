
#pragma once

#include <string>
#include <CppMirror.h>
#include "TestConstants.h"

struct MethodCallTests;
struct ConstructorTests;
struct InheritanceTests;
struct OperatorOverloadTests;

class TestFact
{
	mutable std::string m_fact;
	mutable std::string m_result;
	mutable std::string m_return;
	mutable std::string m_reflReturn;
	mutable std::string m_expectation;

	void TEST(const std::string& pFact) const;
	void EXPECTATION(const std::string& pExpectation) const;

	constexpr void ASSERT_SIGNATURE(const bool pAssert) const;

	template<class _type, class _reflTy>
	void RESULT_DESCRIPTION(std::unique_ptr<_type>& pPtrI, rtl::ReflObject<_reflTy>& pPtrII) const;

	template<class _type, class _reflTy>
	void RESULT_DESCRIPTION(_type& pObj, rtl::ReflObject<_reflTy>& pPtr) const;

	template<class _type, class _reflTy>
	constexpr void ASSERT_STATES_EQUAL(const _type& pObj, rtl::ReflObject<_reflTy>& pPtr) const;

	template<class _type, class _reflTy>
	constexpr void ASSERT_STATES_EQUAL(std::unique_ptr<_type>& pPtrI, rtl::ReflObject<_reflTy>& pPtrII) const;

public:

	TestFact();

	friend MethodCallTests;
	friend ConstructorTests;
	friend InheritanceTests;
	friend OperatorOverloadTests;

	const std::string& fact() const;
	const std::string& result() const;
	const std::string& expectation() const;
};