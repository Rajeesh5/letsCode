#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

class Event {
 public:
  explicit Event(const std::string& topic) : topic_(topic) {}

  template <typename T>
  void AddProperty(const std::string& key, T&& value) {
    properties_[key] = std::make_shared<Model<T>>(std::forward<T>(value));
  }

  template <typename T>
  const T& GetProperty(const std::string& key) const {
    static const T defaultPropertyValue{};
    auto it = properties_.find(key);
    if (it != properties_.end()) {
      auto modelPtr = std::static_pointer_cast<Model<T>>(it->second);
      // return modelPtr->get();
      return modelPtr->get();
    }
    // Return a default-constructed value if property is not found
    return defaultPropertyValue;
  }

  std::string GetTopic() const { return topic_; }

  std::vector<std::string> GetPropertyNames() const {
    std::vector<std::string> names;
    for (const auto& pair : properties_) {
      names.push_back(pair.first);
    }
    return names;
  }

  bool ContainsProperty(const std::string& key) const {
    return properties_.find(key) != properties_.end();
  }

 private:
  struct Concept {
    virtual ~Concept() = default;

    virtual const void* get() const = 0;

    template <typename T>
    const T& get() const {
      return static_cast<const Model<T>*>(this)->data_;
    }
  };

  template <typename T>
  struct Model : Concept {
    explicit Model(T&& data) : data_(std::forward<T>(data)) {}
    T data_;
  };

  std::string topic_;
  std::map<std::string, std::shared_ptr<Concept>, std::less<>> properties_;
};

int main() {
  Event event("TestEvent");
  int intValue = 42;
  double doubleValue = 3.14;
  std::string stringValue = "Hello";

  event.AddProperty("intProperty", intValue);

  event.AddProperty("doubleProperty", doubleValue);
  event.AddProperty("stringProperty", stringValue);

  std::cout << "Event Topic: " << event.GetTopic() << std::endl;
  std::cout << "Properties:" << std::endl;
  for (const auto& name : event.GetPropertyNames()) {
    std::cout << name << std::endl;
  }

  std::cout << event.GetProperty<int>("intProperty") << std::endl;

  /*

    std::cout << event.GetProperty<double>("doubleProperty") << std::endl;
  std::cout << event.GetProperty<std::string>("stringProperty") << std::endl;
      for (const auto& name : event.GetPropertyNames()) {
      std::cout << name << ": "
                << *event.GetProperty<decltype(event.GetProperty(name))>(name)
                << std::endl;
    }
  */
  return 0;
}
