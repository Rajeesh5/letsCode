#ifndef SDOOR_HPP_
#define SDOOR_HPP_

#include "door.hpp"
#include "buzzer.hpp"
#include "apiLogger.hpp"
#include "IFormatter.hpp"
#include <memory>

class SmartDoor: public Door {

public:
    SmartDoor (std::shared_ptr<IApiLogger> logger,
               std::shared_ptr<IBuzzer> buzzer);

    void setFormatter() {}
    void open() override {
        Door::open();
        buzzer_->makeNoise(2);
        apilogger_->write("Door Open");
    }
    void close() override {
        Door::close();
        buzzer_->makeNoise(2);
        apilogger_->write("Door Open");

    }

private:
    std::shared_ptr<IFormatter> formater_;
    std::shared_ptr<IBuzzer>  buzzer_;
    std::shared_ptr<IApiLogger> apilogger_;
};
#endif