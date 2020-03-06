### and a full example

The SimpleString class is a bit ugly, but how to demonstrate that when you're using STL?

```cpp
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <utility>
#include <iostream>

struct SimpleString {
  SimpleString(size_t max_size)
      : max_size{ max_size }
      , length{} {
    if(max_size == 0) {
      throw std::runtime_error{ "Max size must be at least 1." };
    }
    buffer = new char[max_size];
    buffer[0] = 0;
  }
  ~SimpleString() {
    delete[] buffer;
  }
  SimpleString(const SimpleString& other)
      : max_size{ other.max_size }
      , buffer{ new char[other.max_size] }
      , length{ other.length } {
    std::strncpy(buffer, other.buffer, max_size);
  }
  SimpleString(SimpleString&& other) noexcept
      : max_size(other.max_size)
      , buffer(other.buffer)
      , length(other.length) {
    other.length = 0;
    other.buffer = nullptr;
    other.max_size = 0;
  }
  SimpleString& operator=(const SimpleString& other) {
    if(this == &other)
      return *this;
    const auto new_buffer = new char[other.max_size];
    delete[] buffer;
    buffer = new_buffer;
    length = other.length;
    max_size = other.max_size;
    std::strncpy(buffer, other.buffer, max_size);
    return *this;
  }
  SimpleString& operator=(SimpleString&& other) noexcept {
    if(this == &other)
      return *this;
    delete[] buffer;
    buffer = other.buffer;
    length = other.length;
    max_size = other.max_size;
    other.buffer = nullptr;
    other.length = 0;
    other.max_size = 0;
    return *this;
  }
  void print(const char* tag) const {
    std::cout << tag << ": " << buffer;
  }
  bool set_line(const char* x) {
    length = strlen(x);
    if(length + 2 > max_size)
      return false;
    // NOTE, you might wanna clean buffer
    std::strncpy(buffer, x, length); 
    buffer[length++] = '\n';
    buffer[length] = 0;
    return true;
  }

  private:
  size_t max_size;
  char* buffer;
  size_t length;
};

int main() {
  SimpleString a{ 50 };
  a.set_line("msg a");

  std::cout << "=== copy constructor ===" << std::endl;
  SimpleString b{ a };
  a.print("a");
  b.print("b");

  a.set_line("msg a");
  b.set_line("msg b");
  std::cout << "=== copy assignment ===" << std::endl;
  b = a;
  a.print("a");
  b.print("b");

  std::cout << "=== move constructor ===" << std::endl;
  SimpleString c{ std::move(a) };  
  // a in "moved from", will terminate and I cannot catch, why
  // a.print("a");     
  c.print("c");

  std::cout << "=== move assignment ===" << std::endl;
  c.set_line("msg c");
  b = std::move(c);
  // c is "moved-from"
  b.print("b");
}

// output
// === copy constructor ===
// a: msg a
// b: msg a
// === copy assignment ===
// a: msg a
// b: msg a
// === move constructor ===
// c: msg a
// === move assignment ===
// b: msg c
```