

#ifndef PERSON_H
#define PERSON_H


#include <iostream>
#include <memory>
#include <string>
#include <csignal>

class Person {
    public:
    Person (const int age, const std::string &name):age_(age),name_(name){} 
    ~Person () { std::cout << "Person:: " << name_ << " dies." << std::endl;}
private:
    int age_;
    std::string name_;
};
#endif