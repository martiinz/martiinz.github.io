# Interfaces (134)

Or Runtime Polymorphism

*Interface* is a shared boundary that contains no data/code
*Implementation* is code or Data that declares support for an Interface
Interfaces promote highly reusable and loosely coupled code

Let's see an example where class Bank is *consumer* of the interface Console logger.

```cpp
// the interface
struct Logger{
    virtual ~Logger() = default;
    virtual void log_transfer(int from, int to, double amount) = 0;
};

// implementation console
struct ConsoleLogger : Logger {
    void log_transfer(int from, int to, double amount) override {
        std::cout << "[cons] " << from << "->" << to << " : " << amount << std::endl;
    }
};

// implementation file
struct FileLogger : Logger {
    void log_transfer(int from, int to, double amount) override {
        std::cout << "[file] " << from << "->" << to << " : " << amount << std::endl;
    }
};
```



In cpp interfaces are done with inheritance, there is no interface keyword
The *virtual* keyword permits the derived class to override a base class Method
Use *override* keyword in the implementation to tell the compiler you indented to overwrite. (good practice)
If you want to *require* the derived class to implement the method, append the suffix = 0
Add a virtual destructor to Interface, in rare circumstances it's possible to leak resources otherwise ( see listing 5.9)

## Using Interfaces (144)

- *Constructor injection*, use constructor to set reference (cannot be reseated)
-> use that if implementation stays the same for lifetime of object
- *Property  injection*, use a method to set a pointer member, can be changed at anytime
-> use that if you need to cache implementation 
- You can combine these to methods

```cpp
// constructor injection 
struct Bank {
Bank(Logger& logger) : logger{ logger } {}
    void make_tranfer(int from, int to, double amount){
        logger.log_transfer(from, to, amount);
    }
private:
    Logger& logger;
}
int main() {
    ConsoleLogger logger;
    Bank bank{ logger };
}
```

```cpp
// Property injection
struct Bank {
    void set_logger(Logger* new_logger) {
        logger = new_logger;
    }
    void make_transfer(long from, long to, double amount) {
        if (logger) { // if interface implementation set (no nullptr)
            logger->log_transfer(from, to, amount);
        }
    }
private:
    Logger* logger{};
};
int main() {
    ConsoleLogger console_logger;
    FileLogger file_logger;
    Bank bank;
    bank.set_logger(&console_logger);
    bank.set_logger(&file_logger);
}
```

```cpp
// combined
struct Bank {
    Bank(Logger* logger) : logger{ logger } ()
    void set_logger(Logger* new_logger) {
        logger = new_logger;
    }
    void make_transfer(long from, long to, double amount) {
        if (logger) {
            logger->log_transfer(from, to, amount);
        }
    }
private:
    Logger* logger;
};

```

