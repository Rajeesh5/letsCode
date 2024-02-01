#include <iostream>
#include <map>
#include <memory>
#include <cstring> // for std::strlen
#include <vector>

class PropertyManager {
public:
    // Adds a property to the map
    template <typename T>
    void addProperty(const std::string& name, const T* value, size_t size) {
        properties_[name] = std::make_shared<std::vector<T>>(value, value + size);
    }

    // Retrieves a property by name
    template <typename T>
    const std::vector<T>* getProperty(const std::string& name) const {
        auto it = properties_.find(name);
        if (it != properties_.end()) {
            return std::static_pointer_cast<std::vector<T>>(it->second).get();
        }
        return nullptr;
    }

    ~PropertyManager() {
        // Automatically clean up shared pointers and their allocated memory
        properties_.clear();
    }

private:
    std::map<std::string, std::shared_ptr<void>> properties_;
};

int main() {
    PropertyManager propertyManager;
    char byteArrayValue[] = {'a', 'b', 'c', 'd'};
    
    // Size of the array
    size_t size = std::strlen(byteArrayValue);

    // Add the property to the PropertyManager
    propertyManager.addProperty("char_array", byteArrayValue, size);

    // Retrieve and print the property
    const std::vector<char>* retrievedArray = propertyManager.getProperty<char>("char_array");
    if (retrievedArray) {
        std::cout << "Retrieved char_array: ";
        for (char c : *retrievedArray) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
