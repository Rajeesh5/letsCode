#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

class Event {
 public:
  Event(const std::string& topic) : topic_(topic) {}

  template <typename T>
  void AddProperty(const std::string& key, T&& value) {
    properties_[key] =
        std::make_shared<Model<std::decay_t<T>>>(std::forward<T>(value));
  }

  template <typename T>
  const T* GetProperty(const std::string& key) const {
    auto it = properties_.find(key);
    if (it != properties_.end()) {
      auto modelPtr = std::static_pointer_cast<Concept>(it->second);
      return &modelPtr->get<T>();
    }
    return nullptr;
  }

  const std::string GetTopic() const { return topic_; }

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

  const std::string ToString() const {
    std::string str = "Topic: " + topic_ + "\n";
    for (const auto& pair : properties_) {
      str += pair.first + ": " + pair.second->toString() + "\n";
    }
    return str;
  }

 private:
  struct Concept {
    virtual ~Concept() {}
    virtual std::string toString() const = 0;
    template <typename T>
    const T& get() const {
      return static_cast<const Model<T>*>(this)->data_;
    }
  };

  template <typename T>
  struct Model : Concept {
    Model(T&& data) : data_(std::forward<T>(data)) {}
    std::string toString() const override { return std::to_string(data_); }
    T data_;
  };

  std::string topic_;
  std::map<std::string, std::shared_ptr<Concept>> properties_;
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
    std::cout << name << ": "
              << event.GetProperty<std::decay_t<decltype(intValue)>>(name)
              << std::endl;
  }

  return 0;
}
