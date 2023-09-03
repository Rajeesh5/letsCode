#include<iostream>

class ALA {			// Adorable Little Animal
public:
	virtual void Adoption() = 0;
};

class Puppy :public ALA {
public:
	void Adoption() {
		//Process of Puppy Adoption.
	}
};

class Dog :public ALA {
public:
	void Adoption() {
		//Process of Dog Adoption.
	}
};

void makeAdoption(std::string& choice) {

	ALA* animal;
	// based on choice create adopte animal;
	if (choice._Equal("Dog")) {
		animal = new Dog();
	}
	// use the animal.
	// what happend if throw expection while using Animal
	// never call the delete animal

	// for such case use RAII appoch of smart pointer. 

	// std::auto_ptr<ALA> animal(new Dog);



	delete animal;

}

int main() {



}