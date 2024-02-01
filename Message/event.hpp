#ifndef COM_BOSCH_COMMON_ITRAMS_EVENT_HPP_
#define COM_BOSCH_COMMON_ITRAMS_EVENT_HPP_

#include "map"
#include "memory"
#include "vector"

class Event {
private:
    std::string topic_;
    std::map<std::string, std::shared_ptr<void>> properties_;
public:
    Event();

    Event(const std::string& topic, 
          const std::map<std::string, std::shared_ptr<void>>&&  properties);    

    template <typename T>
    void addProperty(const std::string& topic, std::shared_ptr<T> value) {
        properties_[topic] = std::static_pointer_cast<void>(value);
    }

};


#endif  // COM_BOSCH_COMMON_ITRAMS_EVENT_HPP_