#include <string>

class Singleton final {
public:
    static Singleton& getInstance() {
    static Singleton theInstance { };
        return theInstance;
    }
    int doSomething() {
        return 42;
    }
    std::string doThis() {
        return "Dothis";
    }
    
    // ...more member functions doing more or less useful things here...

    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) noexcept = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) noexcept = delete;
    
private:
    Singleton() = default; 

// ...
};
