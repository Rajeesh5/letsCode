#include "animal.hpp"
#include <memory>

class Lion {

public:
    Lion(std::shared_ptr<IAnimal> animal):animal_(animal){
    }
    void sayHello() { std::cout << "I am Lion" <<std::endl;}
private:
    std::shared_ptr<IAnimal> animal_;
};