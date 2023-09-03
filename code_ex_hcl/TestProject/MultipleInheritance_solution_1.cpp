#include<iostream>

using namespace std;


class Vehicle {
public:
    virtual void safetyCheck() = 0;
};

class Ship : public Vehicle {
public:
    virtual void safetyCheck() override {
        //check if number of lifeboats >= number of passengers
    }
};

class Plane :public Vehicle {

public:
    virtual void safetyCheck() override {
        // check if oxygen mask is in place.
    }
};

// hybrid seaplane was needed which duplicated safety checks of Ship and Plane

class SeaPlane :public virtual Ship,public virtual Plane  {
public:    
    void safetyCheck() {
        // Check if oxygen mask is in place &&
        // Check if number of lifeboats >= number of passengers
        Ship::safetyCheck();
        Plane::safetyCheck();

    }
    
};

// Without establishing a new interface or class for this case you could use the 
// Composition over Inheritance principle. NewSeaPlane has properties of both Plan & Ship

class NewSeaPlane {
private:
    Vehicle* planeProps;
    Vehicle* shipProps;

public:
    void safetyCheck() {
        planeProps->safetyCheck();
        shipProps->safetyCheck();
    }
};

int main() {

    SeaPlane plane;
    plane.safetyCheck();

    NewSeaPlane nplane;
    nplane.safetyCheck();
}





/*
class Address {};
class Department {};
class Program {};

class UniversityPersonnel {

public:
    virtual string getName() const =0;
    virtual Address getAddress() const = 0;
    virtual long getID() const =0;
};


class Teacher : public  virtual UniversityPersonnel {
public:

    virtual string getName() const override {};
    virtual Address getAddress() const override {};
    virtual long getID() const override {};

    Department getDept() const;
    double getSalary();
};

class Student : public virtual UniversityPersonnel {

public:

    virtual string getName() const override {};
    virtual Address getAddress() const override {};
    virtual long getID() const override {};

    Program getMajor() const;
    int getQualityPoints() const;
    int getCredits() const;
    double gpa() const;
};

class GTA : public  Teacher, public Student {};


int main() {

    // UniversityPersonnel up;          // since, Abstract base class; 
    Student s;
    Teacher t;
    //GTA gta;

    //gta.getName();                    
    //gta.getID();
    //string nm4 = gta.Student::getName();
    //string nm5 = gta.Teacher::getName();

    return 0;
}
*/