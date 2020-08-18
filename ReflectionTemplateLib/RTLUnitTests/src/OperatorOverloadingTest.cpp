
#include <vector>

#include "Book.h"
#include "UnitTestTypes.h"

using namespace std;
using namespace rtl;

extern const CppMirror<>& Reflection();

const vector<TestFunctor> OperatorOverloadingTest::UNIT_TEST_CASES = {

	____REFLECTION_UNIT_TEST_CASE____
	{
		fact.TEST("OPERATOR OVERLOADING : EXPLICIT OPERATOR INVOCATION");
		fact.EXPECTATION("1. Method { const bool Date::operator==(const Date&) const } should be invoked by reflection without fail.\n\t"
						 "2. Return value of operator invoked by direct call & Reflection must be same.\n\t"
						 "3. Both operator invocation must leave the respective objects in same state.");

		const Date date1("8/12/2007"), date2("12/3/2050"), date3("8/12/2007");

		auto structDate = Reflection().getClass("Date");
		auto reflDate = ReflObject<>::create(new Date(date1), structDate.getReflClassId());

		auto isEqualsTo = structDate.getMethod("operator==");

		fact.ASSERT_SIGNATURE(isEqualsTo.isSignature<const bool, const Date&>());

		fact.m_return = (date1 == date3 ? "Equal" : "NotEqual");
		fact.m_return += (date1 == date2 ? "Equal" : "NotEqual");
		fact.m_reflReturn = isEqualsTo(reflDate).invoke<const bool, const Date&>(date3) ? "Equal" : "NotEqual";
		fact.m_reflReturn += isEqualsTo(reflDate).invoke<const bool, const Date&>(date2) ? "Equal" : "NotEqual";

		fact.ASSERT_STATES_EQUAL(date1, reflDate);
		fact.RESULT_DESCRIPTION(date1, reflDate);
	},

	____REFLECTION_UNIT_TEST_CASE____
	{
		//This is not Implemented properly yet. In Progress.
		fact.TEST("OPERATOR OVERLOADING : IMPLICIT OPERATOR INVOCATION");
		fact.EXPECTATION("Method { const bool Date::operator==(const Date&) const } should be invoked\n\timplicitly by ReflObject<> without fail.");

		const Date date1("8/12/2007"), date2("12/3/2050"), date3("8/12/2007");

		auto structDate = Reflection().getClass("Date");
		auto reflDate = ReflObject<>::create(new Date(date1), structDate.getReflClassId());

		auto isEqualsTo = structDate.getMethod("operator==");

		fact.ASSERT_SIGNATURE(isEqualsTo.isSignature<const bool, const Date&>());

		fact.m_return = (date1 == date3 ? "Equal" : "NotEqual");
		fact.m_return += (date1 == date2 ? "Equal" : "NotEqual");
		fact.m_reflReturn = isEqualsTo(reflDate).invoke<const bool, const Date&>(date3) ? "Equal" : "NotEqual";
		fact.m_reflReturn += isEqualsTo(reflDate).invoke<const bool, const Date&>(date2) ? "Equal" : "NotEqual";

		fact.ASSERT_STATES_EQUAL(date1, reflDate);
		fact.RESULT_DESCRIPTION(date1, reflDate);
	}
};