
#include <cassert>
#include <iostream>

#include "src/TestFact.h"
#include "src/UnitTestTypes.h"

template<class _testsType>
void execute()
{
	for (const auto performTest : _testsType::UNIT_TEST_CASES)
	{
		const TestFact testObject;
		
		performTest(testObject);

		std::cout	<< "\n\n************************[" << testObject.fact() << "]*************************\n"
					<< "\n" << testObject.expectation() << "\n" << testObject.result() << "\n";
	}
}

int main()
{
	execute<ConstructorTests>();
	execute<MethodCallTests>();
	execute<InheritanceTests>();
	execute<OperatorOverloadingTest>();
}