#ifndef REVERTABLE_HPP
#define REVERTABLE_HPP

#include <memory>
#include "Command.hpp"
#include "Revertable.hpp"

class Revertable {
public:
    virtual ~Revertable() = default;
    virtual void undo() = 0;
};

class UndoableCommand : public Command, public Revertable { };
using CommandPtr = std::shared_ptr<UndoableCommand>;

#endif