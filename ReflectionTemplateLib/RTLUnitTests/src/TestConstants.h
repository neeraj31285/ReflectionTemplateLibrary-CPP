#pragma once

#include <string>
#include <memory>
#include <sstream>
#include "Book.h"

#define ____REFLECTION_UNIT_TEST_CASE____ [](const TestFact& fact)

#define STATE_BEGIN std::string("\n") + thisStr(this) + std::string(" : {\n|")
#define STATE_FIELD(_fieldStr, _field) std::string("\n|  ") + _fieldStr + std::string(": \"") + _field + std::string("\",")
#define STATE_FIELD_cb(_fieldStr, _field) std::string("\n|  ") + _fieldStr + std::string(": {") + _field + std::string("},")
#define STATE_END std::string("\n}")

struct TestFact;

using TestFunctor = void(*)(const TestFact&);

static constexpr const double BOOK_PRICE = 89.99;
static constexpr const char* const DATE_STR = "8/9/2020";
static constexpr const char* const BOOK_TITLE = "The Three Muskteers";
static constexpr const char* const BOOK_AUTHOR = "Alexandre Dumas";

static const auto GET_DATE_INSTANCE = []()->Date
{
	return Date(std::string(DATE_STR));
};

static const auto GET_BOOK_INSTANCE = []()->std::unique_ptr<Book>
{
	Book* book = new Book(BOOK_PRICE, BOOK_TITLE);
	book->setAuthor(BOOK_AUTHOR);
	book->setPublishedOn(Date(DATE_STR));
	return std::unique_ptr<Book>(book);
};

template<class _type>
const std::string thisStr(_type* pThis)
{
	std::stringstream ss;
	ss << static_cast<const void*>(pThis);
	return std::string("__this[") + ss.str() + std::string("](") + std::string(typeid(pThis).name()) + std::string(")");
}

template<class _type>
const std::string thisStr(const _type* pThis)
{
	std::stringstream ss;
	ss << static_cast<const void*>(pThis);
	return std::string("__this[") + ss.str() + std::string("](") + std::string(typeid(pThis).name()) + std::string(")");
}