#include "event.hpp" 


 int main() {
    std::map<std::string, std::shared_ptr<void> > propertiesMap =
    {
        {"Int",      std::make_shared<int>(42)},              // Example with int*
        {"Double",   std::make_shared<double>(3.14)},         // Example with double*
    };
    
    Event event("common::EventConstants::TEST_EVENT_TOPIC", std::move(propertiesMap));
    std::shared_ptr<std::string> dayPtr = std::make_shared<std::string>("Sunday!!");
    event.addProperty("Day", dayPtr);
    return 0;
 }
