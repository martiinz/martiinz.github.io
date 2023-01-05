---
title: "STL Algorithm"
excerpt: "some algorithm STL Examples"
tags:
  - cpp
  - STL
categories:
  - cpp
---

## call operator/lambda/std::for_each()

Use stateless funtion objects, further reading [fluent cpp](https://www.fluentcpp.com/2017/01/23/stl-function-objects-stateless-is-stressless/)

```c++
#include <vector>
#include <algorithm>

// use normal function, increase needs to be hardcoded
// Thats not the way, use call operator or lambda instead
void function(double& number)
{
    number += 2;
}

class CallOperator
{
public:
    // "store" increase Value in constuctor
    explicit CallOperator(double bumpValue) : bumpValue_(bumpValue) {}
    void operator()(double& number) const
    {
        number += bumpValue_;
    }
private:
    double bumpValue_;
};

std::vector<double> numbers = {1, 2, 3, 4, 5};

int main()
{
    std::for_each(numbers.begin(), numbers.end(), function);

    std::for_each(numbers.begin(), numbers.end(), CallOperator(2));

    // or use lambda 
    double bumpValue = 2;
    std::for_each(numbers.begin(), numbers.end(),
              [bumpValue](double& number){number += bumpValue;});
};
```

## std::transform()

Incremental update, update m_logline with non empy fields from vecline

```c++
#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    std::vector<std::string> m_logline{"1", "3", "asdf", "hello"};
    std::vector<std::string> vecline{"1", "4", "", "ciao"};
    // output: 1, 4, asdf, ciao

    // update m_logline with non empy fields from vecline
    // https://en.cppreference.com/w/cpp/algorithm/transform (form 3)
    //             input1.first       input1.last      input2.first     output.first
    std::transform(m_logline.begin(), m_logline.end(), vecline.begin(), m_logline.begin(),
        [](auto const& input1, auto const& input2) {
            return input2.empty()? input1 : input2;
        }
    );

    for(const auto &i : m_logline)
    {
        std::cout << i << ", ";
    }
    std::cout << std::endl;
};
```

## std::find_if()

Find index, subindex of CAN message in a list of structs

```c++
#include <string>
#include <iostream>
#include <algorithm>
#include <map>
 
struct canEntry {
    unsigned int index{};       // canOpen index
    unsigned int subindex{};    // canOpen subindex
    unsigned int val{0};        // actual content
    bool accumulate{false};     // Accumulate register until sent
    bool sent{false};           // not sent ==> keep accumulating
};

std::map <std::string, canEntry> canNodes{
        {"error_register",      { 0x1001, 0x00, 0, true, false}},
        {"status_register",     { 0x1002, 0x00, 0, true, false}},
        {"store_all",           { 0x1010, 0x01 }},
        {"product_code",        { 0x1018, 0x02 }},
        {"serial_number",       { 0x1018, 0x04 }},
};

// set tx4 value from index/subindex
bool setTX4Value(unsigned int index, unsigned int subindex, unsigned int data){
    // find index, subindex
    auto pdo = std::find_if(canNodes.begin(), canNodes.end(),  [&index, &subindex](auto const& a){
                return a.second.index == index
                    && a.second.subindex == subindex;
    }); 

    // set value, if found
    if( pdo != canNodes.end() ){
        // handle the accumulate mode
        if(pdo->second.accumulate){
            if(pdo->second.sent){
                // data sent, set register to actual value
                pdo->second.sent = false;
                pdo->second.val = data;
            } else {
                // accumulate register
                pdo->second.val |= data;
            }
        } else {
            // normal mode, just set data
            pdo->second.val = data;
        }
        return true;
    }
    // value not found
    return false;
}

int main(){
    // find index
    if( setTX4Value(0x1001, 0x00, 0xFE)){
        // access by key
        auto it = canNodes.find("error_register");
        auto key = it->first;
        auto val = it->second.val;
        std::cout << key << ": 0x" << std::hex << val << std::endl;
    }
}
```
