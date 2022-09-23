---
title: "Interface/Inheritance Example"
excerpt: "a minimal interface exaple, switching between mqtt and serial line"
tags:
  - cpp
categories:
  - cpp
---

A minimal interface example. The intention of the full implemetation is to easily switch IOT transmission between the `MQTT protocol` and `plain text on a serial line`

```cpp
#include <string>
#include <iostream>
#include <string_view>
#include <optional>
#include <memory>

// pure virtual interface class
class IotInterface
{
public:
    virtual ~IotInterface() = default;
    virtual void tx(std::string_view value) = 0;
    virtual std::string rx() const = 0;
};

// MQTT implementation
class Mqtt : public IotInterface
{
public:
    void tx(std::string_view value) override;
    std::string rx() const override;
private:
    std::optional<std::string> m_value{"mqtt"};
};

// serial implementation
class Serial : public IotInterface
{
public:
    void tx(std::string_view value) override;
    std::string rx() const override;
private:
    std::optional<std::string> m_value{"serial"};
};

void Serial::tx(std::string_view value) { m_value = value; }
std::string Mqtt::rx() const { return m_value.value_or(""); }

void Mqtt::tx(std::string_view value) { m_value = value; }
std::string Serial::rx() const { return m_value.value_or(""); }

int main()
{
    std::unique_ptr<IotInterface> itf;

    itf = std::make_unique<Serial>();

    std::cout << "rx: " << itf->rx() << std::endl;
    itf->tx("send awsome serial");
    std::cout << "rx: " << itf->rx() << std::endl;

    itf = std::make_unique<Mqtt>();

    std::cout << "rx: " << itf->rx() << std::endl;
    itf->tx("send awsome mqtt");
    std::cout << "rx: " << itf->rx() << std::endl;
};
```
