#include <iostream>
#include <experimental/any>
#include <map>
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

int main() {
    std::map<std::string, std::experimental::any> myMap;

    // Store values in the map
    myMap["integer"] = 42;
    myMap["double"] = 3.14;
    myMap["string"] = std::string("Bosch India");
    myMap["myClass"] = MyClass(123);
    myMap["vector"] = std::vector<int>{1, 2, 3, 4, 5};

    // Retrieve and print the stored values from the map
    for (const auto& pair : myMap) {
        const std::string& key = pair.first;
        const std::experimental::any& value = pair.second;

        std::cout << "Key: " << key << ", Type: ";

        try {
            if (value.type() == typeid(int)) {
                std::cout << "integer, Value: " << std::experimental::any_cast<int>(value);
            } else if (value.type() == typeid(double)) {
                std::cout << "double, Value: " << std::experimental::any_cast<double>(value);
            } else if (value.type() == typeid(std::string)) {
                std::cout << "string, Value: " << std::experimental::any_cast<std::string>(value);
            } else if (value.type() == typeid(MyClass)) {
                const MyClass& myClassObj = std::experimental::any_cast<MyClass>(value);
                std::cout << "MyClass, Value: " << myClassObj.getData();
            } else if (value.type() == typeid(std::vector<int>)) {
                const std::vector<int>& vec = std::experimental::any_cast<std::vector<int>>(value);
                std::cout << "std::vector<int>, Size: " << vec.size();
            } else {
                std::cout << "Unknown type!";
            }
        } catch (const std::experimental::bad_any_cast& e) {
            std::cerr << "Error: " << e.what();
        }

        std::cout << std::endl;
    }

    return 0;
}