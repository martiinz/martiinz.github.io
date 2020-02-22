# Exceptions

trow std::runtime_error, searches next catch and function will not return 

```cpp
#include <cstdio>
#include <string>
#include <iostream>
#include <stdexcept>

void spotSwan(const std::string & color){
    if(color == "black"){
        throw std::runtime_error{"blackSwan fail!"};
    }
    std::cout << color << " swan spotted!" << std::endl;
}
int main(){
    try{
        spotSwan("blue");
        spotSwan("green");
        spotSwan("black");
        spotSwan("yellow"); // will not be executed
    } catch (const std::runtime_error& e){
        std::cout << "exception: " << e.what() << std::endl;
    };
}
```

## std::exception class

std::exception has subclasses runtime_error and logic_error (and language support error)

logic errors could be avoided through more careful programming. eg:

- length_error
- out_of_range

runtime errors. eg:

- system_error
- overflow_error

Some other errors are directly derived from std::exception. Eg. bad_alloc, which reports that a new has failed to allocate.

## catching an re-throw (103)

different "catch levels" are available. It's common to see such code in a program's entry code

```cpp
try{
	// code that might thows an exception
} catch ( const std::logic_error& e){
    // Logic error, terminate; there is a programming error
} catch ( const std::runtime_error& e){
    // try to recover
} catch ( const std::exception& e){
    // this will handle any exception that derives from std::exception
} catch (...){
    // Panic, this will catch every error
}
```

```cpp
// the keyword throw will rethrow an error
// when does that make sense? Normally go for specific error first..
try{
    // code that might throws an exception 
} catch (std::exception& e){
    if( e.code() != std::errc::permission_denied){
        throw; //  not permission denied, rethrow
    }
    // handle permission denied
}
```

## user defined exception 

user defined exceptions, usually inherit from std::exception, so that they can be catched with std::exception

```cpp
#include <cstdio>
#include <string>
#include <iostream>
#include <stdexcept>
 
class MyException : public std::exception {
 public:
    const char * what () {
      return "my freakin custom Exception";
   }
};
 
int main() {
   try {
      throw MyException();
   }catch(MyException e) {
      std::cout << e.what() << std::endl;
   } catch(std::exception e) {
      // Other errors or even my exception, if it would not been catched
   }
}
```

## noexcept

You can mark a function that can not throw an exception with noexcept keyword.  

BUT C++ Runtime will call std::terminate if such a function throw an exception

```cpp
bool isOdd(int x) noexcept{
	return x%2;
}
```

## Call Stack and Exception (105)

The runtime seeks the closest exception handler. Any object whose lifetime ends will be destroyed the usual way, when unwinding the call stack.

```cpp
// Trace Object life cycle Example
#include <cstdio>
#include <string>
#include <iostream>

class Tracer {
public:
    Tracer(const std::string name) : name{name}{
        if(name == "error"){
            throw std::runtime_error{"nasty shit!"};
        }
        std::cout << name << " constructed" << std::endl;
    }
    ~Tracer(){
        std::cout << name << " destructed" << std::endl;
    }
private:
    const std::string name;
};

void fn_3(void){
    Tracer t3{"error"};
}

void fn_2(void){
    Tracer t2{"good t2"};
    fn_3(); // destrucing t2, since exception handler "leaves function"
}

int main (){
    try{
        Tracer t1{"good t1"};
        fn_2();
        Tracer t4{"good t4"};  
    } catch (const std::exception& e){
        std::cout << "t1 and t2 are already destroyed here, "
            << "since there lifcycle ended" << std::endl;
        std::cout << e.what();
    }
}

// good t1 constructed
// good t2 constructed
// good t2 destructed
// good t1 destructed
// t1 and t2 are already destroyed here since there lifcycle ended
// nasty shit!
```

## Exception and Performance (113)

- No overhead when no error occurs
- Overhead when error occurs, but huge gain in robustness and maintainability

Use of exception handling leads to programs that are faster when they execute normally and better behaved when they fail ( Kurt Guntheroth)



## Alternatives to Exception (114)

Exception are not always available, eg on Realtime Embedded. You need to track exceptions manually 

```cpp
// 1 Alternative, return multiple values
struct Result{
    myObject o;
    bool valid;
}

Result createObject(void){
    myObject o{};
    // check if o is valid
    bool valid = true;
    return [o, valid];
}

int main(){
    auto [o, valid] = createObject();
    if(!valid){
        // could not create Object
    }
}
```

