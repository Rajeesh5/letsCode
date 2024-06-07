#ifndef PERSONDB_H
#define PERSONDB_H

#include <vector>
#include "Person.h"


class PersonDB {

public:
    void AddPerson(const std::shared_ptr<Person> person){
        db_.push_back(person);
    }
private:
    std::vector<std::shared_ptr<Person>> db_;
};

#endif