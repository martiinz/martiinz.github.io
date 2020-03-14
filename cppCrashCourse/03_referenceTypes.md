# Reference Types

Pointer vs References

## Pointer (68)

- Low level object, used in C
- consists of address and type

```CPP
int * myPtr; // declare with asterisk

int yourVal{};
myPtr = &yourVal; // address-of operator

*myPtr = 33; // derefencing Pointer, access Memory/Value
```

### "->" member-of-Pointer operator
- derefences a Pointer
- Accesses a member of the pointed-to Object

```CPP
// following statemets are equal
clock_ptr->getYear();
(*clock_ptr).getYear();
```
### Pointer and Arrays (72)
```CPP
// decay (zerfallen) Example
int key[]{1,2,3};
int * keyPtr = key; // keyPtr points to 1, but lenght information is lost 
// Pointer Arithmetic
keyPtr++;  			// keyPtr point to 2
```
Pointer are dangerous
- direct Memory Access 
- no bond checking
- use std::byte for raw Memory access

void Pointer, Pointer without type, can not be dereferenced  
nullptr, Pointer value that points nowhere  
boolean: Pointer != nullptr
- converts to true
- usefull to check function returns

### Ponter usage
- datastructures like linked lists
- if you need to change pointers type


## References (77)
References are the safer and more convenient pointers
- cannot be assigned to nullptr
- cannot be reseated (address cannot change)

```CPP
void add_year(clockClass& clock){
    clock.setYear(clock.getYear() + 1); // no derefence needed
}
```



### const Keyword and Initializers List (81)

- const Argument --> readonly argument
- const Method --> read only method
  - can not change class variable
  - no function call of nonconst functions
- const Member variables --> constant Variables 
  - can be set with initializers list, but constant from then on

```cpp
// initializers list "executed" before constructor
#include <cstdio>
#include <string>
#include <iostream>

class Baby {
public:
    Baby(const std::string name, int number)
    : name {name}, born_in {number}{}

    void printme() const {
        std::cout << "hi " << name << " born in " << born_in << std::endl;
    }
    
    // set year generates compiler error "assignment of read-only member"
    void set_year(int year){
        this->born_in = year;
    }

private:
    const std::string name{};
    const int born_in{};
};

int main(){
    Baby kalle{"Kalle", 1999};
    kalle.printme();
}
```

### auto Keyword (84)

When initializing a variable with auto , compiler determines type from context (init, function return, ...)  
auto Keyword helps code making simper and resilient to refactoring

```cpp
auto num{42};   // int
auto lnum{42L}; // long
auto foo{0.3};  // double
auto bar{0.3F}; // float

// works with references, pointers and const
auto & ref = bar; // float &
```

