#include <iostream>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/shared_ptr.hpp>
#include <map>

class MyClass {
public:
    MyClass(int val) : value(val) {}
    ~MyClass() {
        std::cout << "Destructor called for MyClass with value: " << value << std::endl;
    }

    // Other member functions...
private:
    int value;
};

int main() {

  /*  
    boost::ptr_map<int, void> myMap;

    // Inserting objects of different types into the map
    myMap.insert(1, new int(42));
    myMap.insert(2, new float(3.14));
    myMap.insert(3, new MyClass(100));

    // Accessing the values
    std::cout << *myMap[1] << std::endl;  // Should print 42
    std::cout << *myMap[2] << std::endl;  // Should print 3.14
*/


    //boost::ptr_map<int, std::shared_ptr<void>> myMap;

    std::map<int, std::shared_ptr<void>> myMap;

    // Inserting objects of different types into the map
    myMap[1] = std::make_shared<int>(42);
    myMap[2] = std::make_shared<float>(3.14);
    myMap[3] = std::make_shared<MyClass>(100);

    // Accessing the values
    std::cout << *std::static_pointer_cast<int>(myMap[1]) << std::endl;    // Should print 42
    std::cout << *std::static_pointer_cast<float>(myMap[2]) << std::endl;  // Should print 3.14


    
    return 0;
}

// g++  generic_map.cpp -lboost_system -lboost_ptr_container -o generic_map