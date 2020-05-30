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
        }
        // normal mode, just set data
        pdo->second.val = data;
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
