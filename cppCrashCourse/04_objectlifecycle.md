# Object Life Cycle

## Automatic Storage Duration (90)

Within brackets {}

- eg in Function, local Variables

## Static Storage Duration (91)

### Global Static Variable

static object declared with static or extern keyword. They are global or namespace scope.

--> Lifetime = Program Lifetime

### Local Static Variable

- local scope
- lifetime
  - from first function call
  - to program Exit

Static Member are not associated to Object, but to a class

--> only 1 Instance per class

### Thread-Local Static Storage Duration (94)

Same than static, but with own copy for every thread.  
Helps to design thread safe code...

```cpp
static thread_local int myValue{0};
```

## Dynamic Storage Duration (95)

allocation/deallocation on request for fundamental types/arrays/objects

- new
- delete

Missing delete, lead in memory Leak  
delete frees memory but does not clean it. "After free Bug" if you use it accidentally 

```cpp
// Trace Object life cycle Example
#include <cstdio>
#include <string>
#include <iostream>

class Tracer {
public:
    Tracer(const std::string name) : name{name}{
        std::cout << name << " constructed" << std::endl;
    }
    ~Tracer(){
        std::cout << name << " destructed" << std::endl;
    }
private:
    const std::string name;
};

static Tracer t1{"t1_static"};
static thread_local Tracer t2{"t2_thread_local"};

int main (){
    t2;  // needs to be used, https://github.com/JLospinoso/ccc/issues/44
    std::cout << "A" << std::endl;
    Tracer t3{"t3_automatic"};
    std::cout << "B" << std::endl;
    const auto t4 = new Tracer{"t4_dynamic"};
    std::cout << "C" << std::endl;
    // t4 is never destructed without delete statement
    // delete t4;
}

// Output
// t1_static constructed
// t2_thread_local constructed
// A
// t3_automatic constructed
// B
// t4_dynamic constructed
// C
// t3_automatic destructed
// t2_thread_local destructed
// t1_static destructed
```

