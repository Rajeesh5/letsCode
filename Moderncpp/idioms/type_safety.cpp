#include <iostream>
#include <map>
#include <memory>
#include <typeindex>
#include <typeinfo>

using SMap = std::map<std::string, std::shared_ptr<void>, std::less<>>;

class AnyType {
 public:
  template <typename T>
  void AddProperty(const std::string& key, std::shared_ptr<T> value) {
    properties_[key] = std::static_pointer_cast<void>(value);
  }

  template <typename T>
  const T* GetProperty(const std::string& key) const {
    auto it = properties_.find(key);
    if (it != properties_.end()) {
      auto castedPtr = std::static_pointer_cast<T>(it->second);
      return castedPtr.get();
    }
    return nullptr;
  }

 private:
  SMap properties_;
};

/*
class AnyTypeWithTypeIndex {
 public:
  // Method to add a property
  template <typename T>
  void AddProperty(const std::string& key, std::shared_ptr<T> value) {
    properties_[key] = {std::static_pointer_cast<void>(value),
                        std::type_index(typeid(T))};
  }

  // Method to get a property
  template <typename T>
  std::shared_ptr<T> GetProperty(const std::string& key) const {
    auto it = properties_.find(key);
    if (it != properties_.end() &&
        it->second.type == std::type_index(typeid(T))) {
      return std::static_pointer_cast<T>(it->second.ptr);
    }
    return nullptr;
  }

 private:
  struct AnyValue {
    std::shared_ptr<void> ptr;
    std::type_index type;
  };

  std::map<std::string, AnyValue> properties_;
};

*/
class Concept {
 public:
  virtual ~Concept() = default;
};

template <typename T>
class Model : public Concept {
 public:
  Model(T&& value) : object(std::forward<T>(value)) {}
  T object;
};

class TypeErasedMap {
 public:
  template <typename T>
  void insert(const std::string& key, T&& value) {
    map_[key] =
        std::make_unique<Model<std::decay_t<T>>>(std::forward<T>(value));
  }

  template <typename T>
  T* get(const std::string& key) const {
    auto it = map_.find(key);
    if (it != map_.end()) {
      if (auto model = dynamic_cast<Model<T>*>(it->second.get())) {
        return &model->object;
      }
    }
    return nullptr;
  }

 private:
  std::map<std::string, std::unique_ptr<Concept>> map_;
};


// write a class that can store any type of data and retrieve it later
// using a key. The class should have


int main() {
  /*
  AnyType anyType;
  anyType.AddProperty("int", std::make_shared<int>(10));
  anyType.AddProperty("double", std::make_shared<double>(20.369));
  anyType.AddProperty("string", std::make_shared<std::string>("Hello"));

  std::cout << *anyType.GetProperty<int>("int") << std::endl;
  std::cout << *anyType.GetProperty<double>("double") << std::endl;
  std::cout << *anyType.GetProperty<std::string>("string") << std::endl;
*/

  /*
    AnyTypeWithTypeIndex anyType;
    anyType.AddProperty("int", std::make_shared<int>(10));
    anyType.AddProperty("double", std::make_shared<double>(20.369));
    anyType.AddProperty("string", std::make_shared<std::string>("Hello"));

    // Retrieve and verify the properties
    auto intPtr = anyType.GetProperty<int>("int");
    if (intPtr) {
      std::cout << *intPtr << std::endl;
    } else {
      std::cout << "Failed to get int property" << std::endl;
    }

    auto doublePtr = anyType.GetProperty<double>("double");
    if (doublePtr) {
      std::cout << *doublePtr << std::endl;
    } else {
      std::cout << "Failed to get double property" << std::endl;
    }

    auto stringPtr = anyType.GetProperty<std::string>("string");
    if (stringPtr) {
      std::cout << *stringPtr << std::endl;
    } else {
      std::cout << "Failed to get string property" << std::endl;
    }

    // Test for a missing key
    auto missingPtr = anyType.GetProperty<int>("missing");
    if (!missingPtr) {
      std::cout << "Property 'missing' not found, as expected." << std::endl;
    }

    // Test for a type mismatch
    auto typeMismatchPtr = anyType.GetProperty<double>("string");
    if (!typeMismatchPtr) {
      std::cout << "Type mismatch detected, as expected." << std::endl;
    }

  */

  TypeErasedMap typeMap;

  // Storing different types of data
  typeMap.insert("int", 10);
  typeMap.insert("double", 20.369);
  typeMap.insert("string", std::string("Hello"));

  // Retrieving data
  if (int* intValue = typeMap.get<int>("int")) {
    std::cout << "int value: " << *intValue << std::endl;
  }

  if (double* doubleValue = typeMap.get<double>("double")) {
    std::cout << "double value: " << *doubleValue << std::endl;
  }

  if (std::string* stringValue = typeMap.get<std::string>("string")) {
    std::cout << "string value: " << *stringValue << std::endl;
  }

  return 0;
}