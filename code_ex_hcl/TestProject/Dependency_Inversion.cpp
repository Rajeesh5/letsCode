#include<iostream>

/*
class Calculator {
public:
    double Add(double x, double y) {
        return x + y;
    }

    double Subtract(double x, double y) {
        return x - y;
    }
};

Problem: So how do we add new operations (or “extend”) our Calculator class
without actually doing code changes (or “modifications”) to it? This is where
Dependency Inversion Principle (DIP) comes into play.
*/


//Abstraction Layer
class ICalculatorOperation {
public:
    virtual double calculate(double x, double y) = 0;
};

//Low Level Module
class AddCalculatorOperation : public ICalculatorOperation {
public:
    double calculate(double x, double y) {
        return x + y;
    }
};

//Low level Module
class SubtractCalculatorOperation :public ICalculatorOperation {
public:
    double calculate(double x, double y) {
        return x - y;
    }
};

//High level module
class Calculator {
public:
    Calculator(ICalculatorOperation *cal):m_pCal(cal){}
    ~Calculator() { 
        if (m_pCal) {
            delete m_pCal;
        }
    }
    double solve(double x, double y) {
        // Calculations will be based on the "injected" ICalculatorOperation.
        return m_pCal->calculate(x, y);
    }
private:
    ICalculatorOperation* m_pCal;
};


//Driver or client
int main_dependency() {

    Calculator* c1 = new Calculator(new AddCalculatorOperation());
    std::cout << c1->solve(10, 5) << std::endl;

    Calculator* c2 = new Calculator(new SubtractCalculatorOperation());
    std::cout << c2->solve(10, 5) << std::endl;

    delete c1;
    delete c2;

    return 0;
}