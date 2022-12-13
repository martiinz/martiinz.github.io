---
title: "Constructor Inheritance"
excerpt: "call base ctor from derived"
tags:
  - cpp
categories:
  - cpp
---

Respect your parents [Professional C++ Marc Gregoire, Chapter 10]

Objects must be constructed along with their parents and any objects that are contained within them.
C++ defines the creation order as follows:

1. If the class has a base class, the default constructor of the base class is executed, unless there is a call to a base class constructor in the ctor-initializer, in which case that constructor is called instead of the default constructor.

2. Non-static data members of the class are constructed in the order in which they are declared. 

3. The body of the class’s constructor is executed.

```cpp
#include <iostream>
#include <string>

class Base
{
public:
    Base() = delete; // for some reason, do not call default ctor
    explicit Base(int arg) : m_arg(arg)
    {
        std::cout << "ctor Base, arg, " << arg << std::endl;
    }
private:
    int m_arg{}; // mandatory to initialize (eg in case it is an reference)
};

// Derived needs the Base ctor, but no further init
class Derived : public Base
{
    // using directive, CPP core guidlines, C52
    // https://github.com/isocpp/CppCoreGuidelines/blob/9efcaf07f7013fb6d07ee004f936540164535c63/CppCoreGuidelines.md#c52-use-inheriting-constructors-to-import-constructors-into-a-derived-class-that-does-not-need-further-explicit-initialization
    using Base::Base;
};

// DerivedExtended needs the Base ctor, but some more init work
class DerivedExtended : public Base
{
public:
    explicit DerivedExtended(int arg): Base(arg)
    {
        std::cout << "ctor derived extended, arg: " << arg << std::endl;
    };
};

int main()
{
    Base base{2};
    Derived derived{3};
    DerivedExtended derivedext{4};
};

// output:
// ctor Base, arg, 2
// ctor Base, arg, 3
// ctor Base, arg, 4
// ctor derived extended, arg: 4
```
