# Types
## Fundamental Types
see https://en.cppreference.com/w/cpp/language/types
### Integer (32)
To enforce guaranteed integer sizes use int8_t , int16_t, ... see \<cstdint\>

### FloatingPoint (35)
- float (single precision)
- double (double precision)
- long double (extended precision)

### Character Types (36)
- char (1 byte, eg ASCII)
- char16_t (2 byte, eg UTF-16)
- char32_t (4 byte, eg UTF-32)
- wchar_t (large enough to contain largest character, eg UNICODE)


### boolean/int conversion (38)
bool <--> int  
true --> 1  
false --> 0  
true <-- != 0  
false <-- 0 

### std::byte (40)
raw memory access, defined in \<cstddef\>

### size_t (41)
encodes size of object, guaranteed that max value is sufficient to represent max size of all objects  
sizeof( type ) returns size of an object

## array
### init (42)
int array[] = {1, 2, 3, 4}

### range based for loop (44)
```cpp
for( auto i: array )
    std::cout << i << std::endl;
```
## User defined Types
### Enumerations (49)
```cpp
// scoped enum (use unscoped enum for C compatibility)
enum class Race{
    alpha, 
    romeo
};
// init
Race value = Race::romeo;
```
### Plain old Data Class (52)
- simple struct
- C-compatible

### Unions (53)
- struct, but all members share **same** location 
  - = 1 Memoryblock with different Interpretations
  - YOU  need to track valid Interpretation

### Full C++  Class (54)
declared by struct or class keyword, they differ only in default access control  
Apart from that it's a matter of style...

#### struct Keyword
Members public by default  
private by keyword

#### class Keyword
Members private by  default  
public by keyword

#### Constuctor (58)
- Name of class
- with or without Argument
- executed on object init

## Initializing
- 4 Ways cause of C-compliance
- **braced alway applicable --> BRACE YOURSELF**

```cpp
// fundamentals (59)
int a{};    // init to 0
int b{0};   // init to 0 or wathever

// struct (60)
struct c{}; // all struct field init to 0
struct d{"abc", 42} // init struct by values
struct e{"abc"}		// init abc, rest to 0

// array (61)
int arr1[]{1,2,3}	// len3, init
int arr2[3]{}		// len3, init to 0
int arr3[3]{1,2}	// partly inittialized, rest 0

// classes are always initialized by it's constuctor (64)
// but you can initialize members
class Johann {
	int a{0};
	bool braced {true};
}

```

### Narrowing Conversion (63)
Braced init generates warning  on implicit narrowing
```cpp
float a{1};
float b{2};
int narrow(a/b); // copiler silently narows 0.5 to 0
int result{a/b}; // compiler generates warning
```

