#include <iostream>
#include <map>
#include <experimental/any>
#include <vector>



class MyClass {
public:
    MyClass(int value) : data(value) {}

    int getData() const {
        return data;
    }

private:
    int data;
};

class PropertyManager {
public:
    // Adds a property to the map

    void addProperty(const std::string& name, std::experimental::any value) {
        properties_[name] = value;
    }

    // Retrieves a property by name

    std::experimental::any getProperty(const std::string& name) const {
        auto it = properties_.find(name);
        if (it != properties_.end()) {
            return it->second;  // Return the value when the key is found
        }
        return std::experimental::any();  // Return a default-constructed any when the key is not found
    }
/*
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
*/
private:
    std::map<std::string, std::experimental::any> properties_;
};

int main() {
    PropertyManager propertyManager;
    

    propertyManager.addProperty("integer", 42);
    propertyManager.addProperty("double" , 3.14);
    propertyManager.addProperty("string", "Bosch India");
    propertyManager.addProperty("myClass", MyClass(123));
    propertyManager.addProperty("vector" , std::vector<int> {1, 2, 3, 4, 5});

    // Retrieve and print the stored values from the map

    std::experimental::any value;
    try {
        value = propertyManager.getProperty("integer");  
        if (value.type() == typeid(int))
            std::cout << "integer, Value: " << std::experimental::any_cast<int>(value) << std::endl; 
    
        value = propertyManager.getProperty("double");  
        if (value.type() == typeid(double))
            std::cout << "double, Value: " << std::experimental::any_cast<double>(value) << std::endl; 

        value = propertyManager.getProperty("string");  
        if (value.type() == typeid(std::string)) 
            std::cout << "string, Value: " << std::experimental::any_cast<std::string>(value) << std::endl; 

        value = propertyManager.getProperty("myClass");  
        std::cout << "integer, Value: " << std::experimental::any_cast<MyClass>(value).getData() << std::endl; 

        value = propertyManager.getProperty("vector");  
        const std::vector<int>& vec = std::experimental::any_cast<std::vector<int>>(value) ;
        std::cout << "std::vector<int>, Size: " << vec.size() << std::endl;

        for (auto element: vec) {
            std::cout << element << " ";
        }

    } 
    catch (const std::experimental::bad_any_cast& e) {
        std::cerr << "Error: " << e.what();
    }       

    std::cout << std::endl;
    


    return 0;
}
