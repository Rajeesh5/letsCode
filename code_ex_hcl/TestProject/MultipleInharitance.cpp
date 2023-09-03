#include<iostream>

using namespace std;

class Address {};
class Department {};
class Program {};

class UniversityPersonnel {
    
public:
    string getName() const ;
    Address getAddress() const;
    long getID() const;
};

class Teacher : public  UniversityPersonnel {
 public:

 
    Department getDept() const;
    double getSalary();
    void pay(double amount);
};

class Student : public UniversityPersonnel {
   
public:

    Program getMajor() const;
    int getQualityPoints() const;
    int getCredits() const;
    double gpa() const;
};

class GTA : public  Teacher, public Student {
    



};

int main() {

    UniversityPersonnel up;
    Student s;
    Teacher t;
    GTA gta;

    //gta.getName();                    // AMBIGUOUS
    //gta.getID();                    
    //string nm4 = gta.Student::getName();
    //string nm5 = gta.Teacher::getName();

    return 0;
}

