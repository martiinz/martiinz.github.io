---
title: "Copy'n'Paste templates"
excerpt: "cpp copy and paste loops"
tags:
  - cpp
categories:
  - cpp
---

## constructors

### basic ctor syntax

```c++
class myClass
{
  myClass();
  ~myClass();

  // do not move
  myClass(const myClass& other) = delete;
  myClass& operator=(const myClass& other) = delete;

  // do not copy
  myClass(myClass&& other) = delete;
  myClass& operator=(myClass&& other) = delete;
}
```

### initializers list

```c++
DoutState::DoutState(const Config &conf, int par):
  m_conf(conf),
  m_par(par)
{
    /// construct your object here
};
```

### some loops

I barely can remember my own name, how should someone remember the loop syntax in bash, cpp, python at the same time.

```c++
// loop 3 times
for (auto i = 3; i--;)
{
    std::cout << i << std::endl;
}

// loops through a vector
for(const auto &val : {3, 5, 6})
{
    std::cout << val << std::endl;
}
```
