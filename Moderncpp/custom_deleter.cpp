#include <memory>
#include <mutex>
#include <functional>
#include <iostream>

/*
class Component {
public:
    static Component& getInstance() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
            instance_ = std::make_unique<Component>();
        }
        return *instance_;
    }

    void doSomething() {
        std::cout << "Component is doing something." << std::endl;
    }

private:
    // Private destructor
    ~Component() {
        std::cout << "Destructor called for Component." << std::endl;
    }

    static std::unique_ptr<Component> instance_;
    static std::mutex mutex_;

    Component() = default;
    Component(const Component&) = delete;
    Component& operator=(const Component&) = delete;
    Component(Component&&) = delete;
    Component& operator=(Component&&) = delete;
};

std::unique_ptr<Component> Component::instance_;
std::mutex Component::mutex_;

*/
class Component {
public:
    static Component* getInstance() {        
        if (instance_ == nullptr) {
            std::lock_guard<std::mutex> lock(mutex_); 
                
                // Double check within the lock
                if (instance_ == nullptr) {
                    instance_.reset(new Component());
                }
        }        
        return instance_.get();
    }    
    int getState() { return state_;}
    void setSate(int state) { state_ = state;}
 private:
    
    int state_;
    static std::function<void(Component*)> deleter;
    static std::unique_ptr<Component, decltype(Component::deleter)> instance_;
    static std::mutex mutex_;

    Component() = default;
   ~Component() = default;

    Component(const Component&) = delete;
    Component & operator = (const Component &) = delete;
    
    Component(const Component&&) = delete;
    Component & operator = (const Component &&) = delete;

};

// Define the deleter outside the class
std::function<void(Component*)> Component::deleter = [](Component* ptr) { 
    std::cout << "Warning!! going to die" << std::endl;
    delete ptr; 
};

std::unique_ptr<Component, decltype(Component::deleter)> Component::instance_(nullptr, Component::deleter);
std::mutex Component::mutex_;

void fun() {
    Component *object = Component::getInstance();
    std::cout << object->getState() << std::endl;
}

int main() {
    Component *object = Component::getInstance();
    object->setSate(10);
    fun();

    //Component &object = Component::getInstance();
    
    // delete object;

    return 0;
}