#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <cstring>

class MyClass {
public:
    MyClass(int val) : value(val) {}
    ~MyClass() {
        std::cout << "Destructor called for MyClass with value: " << value << std::endl;
    }
    int getValue() { return value; }
    // Other member functions...
private:
    int value;
};


class PropertyManager {
public:
    // Adds a property to the map
    template <typename T>
    void addProperty(const std::string& name, T* value) {
        properties_[name] = std::shared_ptr<T>(value);
    }

    template <typename T>
    T* getProperty(const std::string& name) const {
        auto it = properties_.find(name);
        if (it != properties_.end()) {
            auto castedPtr = std::static_pointer_cast<T>(it->second);
            return castedPtr.get();
        }
        return nullptr;
    }

    template <typename T>
    void addArrayProperty(const std::string& name, const T* value, size_t size) {
        properties_[name] = std::make_shared<std::vector<T>>(value, value + size);
    }

    // Retrieves a property by name
    template <typename T>
    const std::vector<T>* getArrayProperty(const std::string& name) const {
        auto it = properties_.find(name);
        if (it != properties_.end()) {
            return std::static_pointer_cast<std::vector<T>>(it->second).get();
        }
        return nullptr;
    }

    // Checks if a property with the given name exists
    bool containsProperty(const std::string& name) const {
        return properties_.find(name) != properties_.end();
    }

    // Gets a vector of all property names
    std::vector<std::string> getPropertyNames() const {
        std::vector<std::string> result;
        result.reserve(properties_.size());

        for (const auto& entry : properties_) {
            result.push_back(entry.first);
        }
        return result;
    }

private:
    std::map<std::string, std::shared_ptr<void>> properties_;
};

int main() {
    PropertyManager propertyManager;

    int intValue = 42;
    float floatValue = 3.14;
    std::string stringValue = "Hello, C++!";

    propertyManager.addProperty("intProperty", new int(intValue));
    propertyManager.addProperty("floatProperty", new float(floatValue));
    propertyManager.addProperty("stringProperty", new std::string(stringValue));
    propertyManager.addProperty("Custom", new MyClass(123));

    // Check if a property exists
    std::cout << "Contains intProperty: " << std::boolalpha << propertyManager.containsProperty("intProperty") << std::endl;
    std::cout << "Contains nonExistentProperty: " << std::boolalpha << propertyManager.containsProperty("nonExistentProperty") << std::endl;

    // Get all property names
    std::vector<std::string> propertyNames = propertyManager.getPropertyNames();
    std::cout << "Property names: ";
    for (const auto& name : propertyNames) {
        std::cout << name << "\n";
    }
    std::cout << std::endl;

    // Retrieve and print properties
    std::cout << "intProperty: " << *propertyManager.getProperty<int>("intProperty") << std::endl;
    std::cout << "floatProperty: " << *propertyManager.getProperty<float>("floatProperty") << std::endl;
    std::cout << "stringProperty: " << *propertyManager.getProperty<std::string>("stringProperty") << std::endl;
    std::cout << "CustomProperty: " << propertyManager.getProperty<MyClass>("Custom")->getValue() << std::endl;

    // Retrieve and print byte array property
    std::vector<char> byteArrayValue = {'a', 'b', 'c', 'd'};
    
    // Size of the array
    size_t size = byteArrayValue.size();

    // Add the property to the PropertyManager
    propertyManager.addArrayProperty("char_array", byteArrayValue.data(), size);

    // Retrieve and print the property
    const std::vector<char>* retrievedArray = propertyManager.getArrayProperty<char>("char_array");
    if (retrievedArray) {
        std::cout << "Retrieved char_array: ";
        for (char c : *retrievedArray) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
    
    std::vector<int> intArrayValue = {1,2,3,4};
    
    // Size of the array
    size = intArrayValue.size();

    // Add the property to the PropertyManager
    propertyManager.addArrayProperty("int_array", intArrayValue.data(), size);

    // Retrieve and print the property
    const std::vector<int>* retrievedIntArray = propertyManager.getArrayProperty<int>("int_array");
    if (retrievedIntArray) {
        std::cout << "Retrieved char_array: ";
        for (int i : *retrievedIntArray) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }





    return 0;
}
