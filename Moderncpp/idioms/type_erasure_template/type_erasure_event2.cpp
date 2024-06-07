#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

class Event {  // (2)

 public:
  template <typename T>  // (3)
  Event(T&& obj) : object(std::make_shared<Model<T>>(std::forward<T>(obj))) {}

  /*
    template <typename T>
    T get() const {  // (4)
      return object->get<T>();
    }
  */

  template <typename T>
  T get() const {
    return std::static_pointer_cast<const Model<T>>(object)->get();
  }

  struct Concept {  // (5)
    virtual ~Concept() {}
    // template <typename T>
    //  const T& get() const {
    //    return static_cast<const Model<T>*>(this)->object;
    //  }
  };

  template <typename T>  // (6)
  struct Model : Concept {
    Model(const T& t) : object(t) {}

    T get() const { return object; }
    T object;
  };

  std::shared_ptr<const Concept> object;
};

int main() {
  Event e1(10000);
  std::cout << e1.get<int>() << std::endl;

  Event e2("Rajeev");
  std::cout << e2.get<std::string>() << std::endl;

  Event e3(109.369);
  std::cout << e3.get<int>() << std::endl;
}