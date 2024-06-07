#include "smartDoor.hpp"
#include "buzzer.hpp"
#include "apiLogger.hpp"

int main() {

    std::shared_ptr<ApiLogger> logger = std::make_shared<ApiLogger>();
    std::shared_ptr<Buzzer> buzzer = std::make_shared<Buzzer>();

    SmartDoor sd(std::move(logger),std::move(buzzer));
    
    sd.open();
    sd.close();

    return 0;
}