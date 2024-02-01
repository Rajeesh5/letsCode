#include "event.hpp"


Event::Event() {}

Event::Event(const std::string& topic, 
      const std::map<std::string, std::shared_ptr<void>>&&  properties):
      topic_(topic),properties_(std::move(properties)) { 
      }



