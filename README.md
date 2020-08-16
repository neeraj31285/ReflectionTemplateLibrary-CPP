# ReflectionTemplateLibrary-CPP
Reflection Template Library for Modern C++.
- Introspect a class/struct/type, modify objects at run time without dealing with its type at "Compile Time".
- **Static Library**, core functionality is built around the concept of **"Type Erasure"** using Lambdas, without utilizing any RTTI or dynamic_cast.
## Exclusive Features,
- Pure syntatic way of manual registration of types, No need to use any "Mysterious MACROS" at all. Thats Right- **NO MACROS!!**
- No need to add any bit of a code with any class/struct/type declearation or to its implementation. **No code littering, Keep it clean!**
- Manage all the manual registration of any required type in one single implementation unit, away from rest of the code in project.
- Create an Object of **"CppMirror<>"**, pass all type information to reflect as constructor parameter and you're good to GO!
  ```c++
  const CppMirror<> myReflection({/*.. Pass all type information ..*/});
  ```
- Wrap that powerful **(CppMirror<>)** object in a singleton and use C++ Reflection with richness as in Java or c#.

## How To Use,
- Class to reflect - **Person.h** *(Independent of any code related to reflection)*
```c++
#pragma once
#include <string>

class Person
{
    int age;
    std::string name;
public:
    Person() :name("NULLSTR"), age(-1) {}
    Person(std::string pName, int pAge) : name(pName), age(pAge) {}

    int getAge() { return age; }
    void setAge(int pAge) { age = pAge; }
    std::string getName() { return name; }
    void setName(std::string pName) { name = pName; }
};
```
- Do manual registration while creating **CppMirror<>** object.   *(..somwhere in some far far away .cpp file..)*
```c++
#include "ReflectionTemplateBuilder.h"
#include "Person.h"

const CppMirror<>& MyReflection() 
{
    static CppMirror<> cppMirror(
    {
        add<Person, ctor::VOID, ctorArgs<string, int>>("Person")->add(
        {
            {"setAge", add(&Person::setAge)},
            {"getAge", add(&Person::getAge)},
            {"setName", add(&Person::setName)},
            {"getName", add(&Person::getName)},
        }),
        /*
        add<SOME_OTHER_TYPE, DEFAULT_CTOR or <CTOR_WITH_ARGS>...>("TYPE_NAME")->add({
            { "METHOD_NAME", add(METHOD_POINTER)},
            { "METHOD_NAME", add(METHOD_POINTER)},
        })*/
    });
    return cppMirror;
}

```

- In main.cpp, Use **Person** class via Reflection without exposing the **Person Type**.
```c++
#include <iostream>
#include "CppMirror.h"

using namespace std;
extern const rtl::CppMirror<>& MyReflection();

int main()
{
//Get "ReflClass" object from CppMirror<>
  auto classPerson = MyReflection().getClass("Person");
  auto getAge = classPerson.getMethod("getAge");    //(returns instance of ReflMethod)
  auto getName = classPerson.getMethod("getName");
  auto setAge = classPerson.getMethod("setAge");
  auto setName = classPerson.getMethod("setName");
  
//Create Instance using default constructor (the one registered as ctor::VOID)
  auto personObj1 = classPerson.instance();	  //(returns instance of Person wrapped in ReflObject<>)
  
//Syantax : ReflMethod(ReflObject<>).invoke<RETURN_TYPE>()
  int age = getAge(personObj1).invoke<int>();
  string name = getName(personObj1).invoke<string>();
  
//Outputs : Person : { name : NULLSTR, age: -1 }
  cout << "Person : { name : " << name << ", age: " << age << " }";
  
//No need to mention RETURN_TYPE if its void.
  setAge(personObj1).invoke(23);
  setName(personObj1).invoke(string("Krishna"));
  
//Outputs : Person : { name : 23, age: Krishna }
  cout << "Person : { name : " << getAge(personObj1).invoke<int>() 
       << ", age: " << getName(personObj1).invoke<string>() << " }";

//Create instance using overloaded constructor (the one registered as ctorArgs<string, int>)
  auto personObj2 = classPerson.instance(std::string("John Doe"), 37);
  
//Outputs : Person : { name : 37, age: John Doe }
  cout << "Person : { name : " << getAge(personObj2).invoke<int>()
       << ", age: " << getName(personObj2).invoke<string>() << " }";
}
```
