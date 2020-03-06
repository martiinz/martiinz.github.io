# Copy, Move

## Copy

Meaning of Copy:  
x is copied to y --> they are equivalent and independent

- x == y returns true
- modification of x does not affect y

For fundamental and structs (POD) the story is straight forward, just pass by value and you done. It's effective a bitwise copy. 

copying can cost a lost, make sure you really need a copy and prefer passing a const reference.

For fully featured classes (with buffers) it gets more tough. It's a member wise copy by default, which can be dangerous.![](/home/tin/tech_knowledge/martiinz.github.io/cppCrashCourse/pic/04a_copy.png)

If you destruct a an a_copy --> Bang! Double Free! undefined behavior. 

### Copy constructor

Make a deep copy of SimpleString with custom copy constructor

```cpp
// header
SimpleString(const SimpleString& other);

// body
SimpleString(const SimpleString& other)		// const, you must not modify original
    : max_size{ other.max_size }, 			// just copy fundamentals
	  length{ other.length },				
	  buffer{ new char[max_size]} {			// alocate new buffer
	  std::strncopy(buffer, other.buffer, max_size);	// deepcopy buffer
}
```

### copy assignment

Make a deep copy of SimpleString with custom copy assigment.

```cpp
SimpleString& operator=(const SimpleString& other) {
	if (this == &other) return *this;					// check if other refers to this
	const auto new_buffer = new char[other.max_size];	// create new buffer
	delete[] buffer;									// clean old buffer
	buffer = new_buffer;								// and assign new
	length = other.length;								// fundamental cp
	max_size = other.max_size;
	trcpy_s(buffer, max_size, other.buffer);			// deepcopy buffer
return *this;
}
```



### control default behavior

Usually compiler generates a default implementation of copy constructor/assignment. As seen above that likely fails any time a class manages a resource.

Best Practice dictated that you explicitly allow default copy.

- default keyword

Sometimes a class should not be copied, eg class manages files 

- delete keyword

```cpp
// accept default 
class Replicant {
    Replicant(const Replicant&) = default;
	Replicant& operator=(const Replicant&) = default;
};

// delete default
class NoReplicant {
    NoReplicant(const NoReplicant&) = delete;
	NoReplicant& operator=(const NoReplicant&) = delete;
};
}
```

## Move

Copy can be time consuming,  sometime you just want to transfer ownership.  
After moving x to y, object y in in a state called "moved from" state, it can only be (re-)assigned or destructed. 

[..] discussion  about, rvalue and lvalue and some cpp historic [..]

### move constructor

rvalue used &&, cast any object into rvalue with the *std::move()*, see the main() listing  
Use noexcept, since most compilers can not handle exceptions in move an would use copy instead...

```cpp
SimpleString(SimpleString&& other) noexcept		// other is rvalue (&&),
    											// you're allowed to canibalize
    : max_size{ other.max_size }, 
	  buffer(other.buffer),
	  length(other.length) {
          other.length = 0;						// put in "moved from" state
          other.buffer = nullptr;				// delocate other has no impact now
          other.max_size = 0;
      }
```

### move assignment

```cpp
SimpleString& operator=(SimpleString&& other) noexcept {
    if ( this == &other ) return *this;			// jokester, selfreference check
    delete buffer;								// cleanup
    buffer = other.buffer;						// assign
    length = other.length;
    max_size = other.max_size;
    other.buffer = nullptr;						// put in "moved from"
    other.lenght = 0;
    other.max_size = 0;
    return *this;
}
```

## The rule of five

The Rule of five = five Methods are to specify. Either default/delete or implement them appropriate

- destructor
- copy constructor
- move constructor
- copy assignment
- move assignment

If you provide nothing the compiler will generate all of them *rule of zero* 

![](/home/tin/tech_knowledge/martiinz.github.io/cppCrashCourse/pic/04b_contructor.svg)