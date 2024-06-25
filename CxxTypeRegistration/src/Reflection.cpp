#include "Reflection.h"
#include "Reflect.hpp"

//User defined types to be reflected.
#include "Complex.h"
#include "Date.h"
#include "Book.h"

using namespace std;
using namespace nsdate;
using namespace rtl::access;
using namespace rtl::builder;

CxxMirror& MyReflection::instance()
{
	static CxxMirror cxxMirror({

		//Global function, not contained in any namespace.
		Reflect().function("getComplexNumAsString").build(getComplexNumAsString),
		Reflect().function<std::string>("reverseString").build(reverseString),
		Reflect().function<const char*>("reverseString").build(reverseString),

		//Global functions, in "complex" namespace.
		Reflect().nameSpace("complex").function("setReal").build(complex::setReal),
		Reflect().nameSpace("complex").function("setImaginary").build(complex::setImaginary),
		Reflect().nameSpace("complex").function("getMagnitude").build(complex::getMagnitude),

		//"Date" struct, in test_project namespace. Ctor, Date()
		Reflect().nameSpace("nsdate").record<Date>("Date").constructor().build(),
		//Ctor, Date(std::string)
		Reflect().nameSpace("nsdate").record<Date>("Date").constructor<string>().build(),
		//Ctor, Date(unsigned, unsigned, unsigned)
		Reflect().nameSpace("nsdate").record<Date>("Date").constructor<unsigned, unsigned, unsigned>().build(),

		//class Book, no namespace. constructors builds.
		Reflect().record<Book>("Book").constructor().build(),
		Reflect().record<Book>("Book").constructor<double, string>().build()

		////class Book, Methods
		//Reflect().record("Book").function("getPublishedOn").build(&Book::getPublishedOn),
		////Overloaded Methods
		//Reflect().record("Book").function("updateBookInfo").build(&Book::updateBookInfo)
	});

	return cxxMirror;
}