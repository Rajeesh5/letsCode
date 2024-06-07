
#include "superhuman.hpp"
#include "lion.hpp"

    void SuperHuman::Runner() {
        // Init
        std::cout << "I am quick Runner" << std::endl;

        // Lion is EventAdmin
        Lion jambo(std::static_pointer_cast<IAnimal>(shared_from_this()));
        jambo.sayHello();
      
    }
    void SuperHuman::QuickThinker() {
        // HandleEvent
        std::cout << "I am quick Thinker" << std::endl;
    }

