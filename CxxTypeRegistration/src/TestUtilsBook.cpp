
#include "TestUtilsBook.h"
#include "TestUtilsGlobals.h"

//User defined types.
#include "Book.h"

using namespace std;
using namespace nsdate;

namespace test_utils
{
	const bool book::assert_zero_instance_count()
	{
		return (Book::getInstanceCount() == 0);
	}


	template<>
	const bool book::test_stack_instance_ctor<>(const any& pInstance)
	{
		return (Book() == any_cast<Book>(pInstance));
	}


	template<>
	const bool book::test_stack_instance_ctor<double, string>(const any& pInstance)
	{
		return (Book(PRICE, TITLE) == any_cast<Book>(pInstance));
	}


	const bool book::test_method_getPublishedOn_return(const std::string& pRetStr)
	{
		Book bookObj;
		return (bookObj.getPublishedOn() == pRetStr);
	}


	template<>
	const bool book::test_heap_instance_ctor<>(const any& pInstance)
	{
		Book* rbook = any_cast<Book*>(pInstance);
		if (rbook == nullptr) {
			return false;
		}
		return (Book() == *rbook);
	}


	template<>
	const bool book::test_heap_instance_ctor<double, string>(const any& pInstance)
	{
		Book* rbook = any_cast<Book*>(pInstance);
		if (rbook == nullptr) {
			return false;
		}
		return (Book(PRICE, TITLE) == *rbook);
	}


	const bool book::test_method_setAuthor(const any& pInstance)
	{
		Book* rbook = any_cast<Book*>(pInstance);
		if (rbook == nullptr) {
			return false;
		}

		Book book;
		book.setAuthor(AUTHOR);
		return (book == *rbook);
	}


	template<>
	const bool book::test_method_updateBookInfo<>(const any& pInstance) 
	{
		Book* rbook = any_cast<Book*>(pInstance);
		if (rbook == nullptr) {
			return false;
		}

		Book book;
		book.updateBookInfo();
		return (book == *rbook);
	}


	template<>
	const bool book::test_method_updateBookInfo<const char*, double, string>(const any& pInstance)
	{
		Book* rbook = any_cast<Book*>(pInstance);
		if (rbook == nullptr) {
			return false;
		}

		Book book;
		book.updateBookInfo(TITLE, PRICE, string(AUTHOR));
		return (book == *rbook);
	}


	template<>
	const bool book::test_method_updateBookInfo<string, double, const char*>(const any& pInstance)
	{
		Book* rbook = any_cast<Book*>(pInstance);
		if (rbook == nullptr) {
			return false;
		}

		Book book;
		book.updateBookInfo(string(AUTHOR), PRICE, TITLE);
		return (book == *rbook);
	}
}