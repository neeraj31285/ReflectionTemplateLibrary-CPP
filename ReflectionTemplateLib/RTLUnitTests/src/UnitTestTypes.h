#pragma once

#include <vector>
#include "TestFact.hpp"

struct ConstructorTests 
{ 
	static const std::vector<TestFunctor> UNIT_TEST_CASES; 
};

struct MethodCallTests 
{ 
	static const std::vector<TestFunctor> UNIT_TEST_CASES; 
};

struct InheritanceTests 
{ 
	static const std::vector<TestFunctor> UNIT_TEST_CASES; 
};

struct OperatorOverloadingTest 
{ 
	static const std::vector<TestFunctor> UNIT_TEST_CASES; 
};