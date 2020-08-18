
#include <vector>

#include "Book.h"
#include "UnitTestTypes.h"

using namespace std;
using namespace rtl;

extern const CppMirror<>& Reflection();

const vector<TestFunctor> MethodCallTests::UNIT_TEST_CASES = {

	____REFLECTION_UNIT_TEST_CASE____
	{
		fact.TEST("METHOD INVOCATION : RETURNS VALUE");
		fact.EXPECTATION("1. Method { string Book::getAuthor() } should be invoked by reflection without fail.\n\t"
						 "2. Return value of methods invoked by direct call & Reflection must be same.\n\t"
						 "3. Both method invocation must leave the respective objects in same state.");

		auto book = GET_BOOK_INSTANCE();
		auto bookClass = Reflection().getClass("Book");
		auto reflBook = ReflObject<>::create(GET_BOOK_INSTANCE(), bookClass.getReflClassId());
		auto getAuthor = bookClass.getMethod("getAuthor");

		fact.ASSERT_SIGNATURE(getAuthor.isSignature<string>());

		fact.m_return = book->getAuthor();
		fact.m_reflReturn = getAuthor(reflBook).invoke<string>();

		fact.ASSERT_STATES_EQUAL(book, reflBook);
		fact.RESULT_DESCRIPTION(book, reflBook);
	},

	____REFLECTION_UNIT_TEST_CASE____
	{
		fact.TEST("OVERLOADED METHOD INVOCATION: ARGS DIFFERENT VALUE TYPE COUNT");
		fact.EXPECTATION("1. Method { void Book::setPublishedOn(int, int, int) } should be invoked by reflection without fail.\n\t"
						 "2. Methods invoked by direct call & Reflection must leave the respective objects in same state.");

		auto book = GET_BOOK_INSTANCE();
		auto bookClass = Reflection().getClass("Book");
		auto reflBook = ReflObject<>::create(GET_BOOK_INSTANCE(), bookClass.getReflClassId());
		auto setPublishedOn = bookClass.getMethod("setPublishedOn");

		fact.ASSERT_SIGNATURE(setPublishedOn.isSignature<void, int, int, int>());

		book->setPublishedOn(10, 12, 1982);
		setPublishedOn(reflBook).invoke(10, 12, 1982);

		fact.ASSERT_STATES_EQUAL(book, reflBook);
		fact.RESULT_DESCRIPTION(book, reflBook);
	},

	____REFLECTION_UNIT_TEST_CASE____
	{
		fact.TEST("OVERLOADED METHOD INVOCATION: ARGS REFERENCE TYPE");
		fact.EXPECTATION("1. Method { void Book::setPublishedOn(Date&) } should be invoked by reflection without fail.\n\t"
						 "2. Methods invoked by direct call & Reflection must leave the respective objects in same state.");

		auto book = GET_BOOK_INSTANCE();
		auto dateObj = GET_DATE_INSTANCE();
		auto bookClass = Reflection().getClass("Book");
		auto reflBook = ReflObject<>::create(GET_BOOK_INSTANCE(), bookClass.getReflClassId());
		auto setPublishedOn = bookClass.getMethod("setPublishedOn");

		fact.ASSERT_SIGNATURE(setPublishedOn.isSignature<void, Date&>());

		book->setPublishedOn(dateObj);
		setPublishedOn(reflBook).invoke<void, Date&>(dateObj);

		fact.ASSERT_STATES_EQUAL(book, reflBook);
		fact.RESULT_DESCRIPTION(book, reflBook);
	},

	____REFLECTION_UNIT_TEST_CASE____
	{
		fact.TEST("OVERLOADED METHOD INVOCATION: ARGS CONST REFERENCE TYPE");
		fact.EXPECTATION("1. Method { void Book::setPublishedOn(const Date&) } should be invoked by reflection without fail.\n\t"
						 "2. Methods invoked by direct call & Reflection must leave the respective objects in same state.");

		auto book = GET_BOOK_INSTANCE();
		auto bookClass = Reflection().getClass("Book");
		auto reflBook = ReflObject<>::create(GET_BOOK_INSTANCE(), bookClass.getReflClassId());
		auto setPublishedOn = bookClass.getMethod("setPublishedOn");

		fact.ASSERT_SIGNATURE(setPublishedOn.isSignature<void, const Date&>());

		book->setPublishedOn(GET_DATE_INSTANCE());
		setPublishedOn(reflBook).invoke<void, const Date&>(GET_DATE_INSTANCE());

		fact.ASSERT_STATES_EQUAL(book, reflBook);
		fact.RESULT_DESCRIPTION(book, reflBook);
	}
};
