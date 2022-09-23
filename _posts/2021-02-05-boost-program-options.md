---
title: "Boost Programm options example"
excerpt: ""
tags:
  - cpp
  - boost
categories:
  - cpp
---

How to get command line options in c++...

```cpp

// header
#ifndef OPTIONS_H_
#define OPTIONS_H_

#include <stdlib.h>
#include <iostream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

class Options {
public:
    bool readOptions(int ac, char* av[]);
    std::string getInterface(void){ return interface_name; }

private:
    std::string interface_name{};
};

#endif /* OPTIONS_H_ */
```

```c++
// implementation
#include "Options.h"

bool Options::readOptions(int ac, char* av[]){
    try
    {
        po::options_description desc("options");
        desc.add_options()
            ("help,h", "this help")
            ("itf,i", po::value<std::string>(&interface_name)  
                -> default_value("eth0"), "interface name");

        po::variables_map vm;
        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);

        if (vm.count("help"))
        {
            std::cout << desc << "\n";
            return false;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "error: " << e.what() << "\n";
        return 1;
    }
    catch(...)
    {
        std::cerr << "Exception of unknown type!\n";
    }
    return true;
}
```

```c++
// main.h
#include <iostream>
#include "Options.h"

int main(int ac, char** av)
{
    Options opt{};

    if(!opt.readOptions(ac, av))
    {
        return 0;
    }

    auto itf = opt.getInterface();
    std::cout << "itf: " << itf << std::endl;
    
    return 0;
}
```
