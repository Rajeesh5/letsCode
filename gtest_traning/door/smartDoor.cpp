    
#include "smartDoor.hpp"   

SmartDoor::SmartDoor (std::shared_ptr<IApiLogger> logger,
               std::shared_ptr<IBuzzer> buzzer): buzzer_(buzzer),
                                                apilogger_(logger) {}