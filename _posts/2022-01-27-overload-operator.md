---
title: "Operator overloading"
excerpt: "examples on <<, =="
tags:
  - cpp
categories:
  - cpp
---

## Outside class

Example print vector

```c++
#include <string>
#include <vector>
#include <iostream>
#include <iterator>

template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    copy(v.begin(), v.end(), std::ostream_iterator<T>(os, ", "));
    return os;
}

int main(void)
{
    std::vector<int> a{1, 2, 3, 4, 5, 6};
    std::cout << "my vec: " << a << std::endl;
}

// output "my vec: 1, 2, 3, 4, 5, 6,"
```

## Inside class

To get cout accept your class declare operator<< as friend, see [Microsoft cpp](https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170)

```c++
#include <string>
#include <iostream>

#include <string>

struct error_description_t
{
    std::string m_component{""};
    std::string m_field{""};

    error_description_t(const std::string &component="default", const std::string &field="default"):
        m_component(component),
        m_field(field)
    {
        // come ctor work
    }

    // os stream operator
    friend std::ostream& operator <<(std::ostream& os, const error_description_t& e) 
    {
        os << "error_description { "
            << "\n\tcomponent:      " << e.m_component
            << "\n\tfield:          " << e.m_field
            << "\n}";
            return os;
    }

    // compare operator
    // Note cpp 20 has the <=> operator
    inline bool operator== (const error_description_t &rhs) const
    {
        return this->m_component == rhs.m_component &&
            this->m_field == rhs.m_field;
    }

    inline bool operator!= (const error_description_t &rhs) const
    {
        return !(*this == rhs);
    };
};

int main()
{
    error_description_t err1{};
    error_description_t err2{"a", "b"};
    error_description_t err3{"a", "b"};

    // osstream operator
    std::cout << err1 << std::endl;

    // == operator
    std::cout << "err1 == err2: " << (err1 == err2) << std::endl;
    std::cout << "err1 != err2: " << (err1 != err2) << std::endl;
    std::cout << "err3 == err2: " << (err3 == err2) << std::endl;
};

```
