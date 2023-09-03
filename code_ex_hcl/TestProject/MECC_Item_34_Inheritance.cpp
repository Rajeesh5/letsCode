#include<iostream>

using namespace std;

class Shape {
public:
	virtual void drow() = 0;							// Inharit only interface
	virtual void error(const std::string& msg) {        // Inharit interface and Implimention, but we can override 
		defaultError(msg);								// the behaviour on derived classes.
	}
	int getObjectCode() {                               // Inharit interface and mandratoty Implimention.
		// logic for return unique_code..				// Never ever redefine the non virtual function.
		return 1;
	}

protected:
	void defaultError(const std::string& msg){
		cout << "Default Error code:: " << msg << endl;
	}
};

class Eclipse :public Shape {

public:
	virtual void drow() {
		cout << "Its Eclipse Drow()\n";
	}

	virtual void error(const std::string& msg) {
		cout << "Spacial Error code for Eclipse :: " << msg << endl;
	}

};

class Circle :public Shape {
	public:
	virtual void drow() {
			cout << "Its Circle Drow()\n";
	}
	// No errorCode() use default one.


	// Wrong implimetion of non-virtual function.
	int getObjectCode() {
		return 2;
	}

};

int main() {

	std::unique_ptr<Shape> ps = make_unique<Eclipse>();
	//std::unique_ptr<Shape> ps(new Eclipse());

	ps->drow();
	ps->error("Ecli001");

	ps = make_unique<Circle>();
	ps->error("Cir0026");

	// See the problem, ps hold the object of Circle, and expected to 
	// return the objectCode 2 for circle, but based of static type (Shape)
	// it return code = 1.
	cout << ps->getObjectCode() << endl;

	return 0;

}


