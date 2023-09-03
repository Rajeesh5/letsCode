#include "Header.h"
#include <string>

class Knife{
public:
	virtual void sharpen() = 0;
	virtual void polish() = 0;
	virtual void package() = 0;
};

class SteakKnife: public Knife {
public:
	void sharpen(){}
	void polish() {}
	void package(){}
};

class ChefsKnife: public Knife {
public:
	void sharpen() {}
	void polish() {}
	void package() {}
};


//Client Code.

class KnifeShop {
public:
	Knife* createKnife(std::string knifeType) {
		Knife* knife =NULL;
		// create Knife object
		if(knifeType.compare("steak")) {
			knife = new SteakKnife();
		}
		else if (knifeType.compare("chefs")) {
			knife = new ChefsKnife();
		}
		knife->sharpen();
		knife->polish();
		knife->package();

		return knife;
	}

};


class KnifeFactory {
public:
	Knife* createKnife(std::string knifeType) {
		Knife* knife = NULL;
		// create Knife object
		if (knifeType.compare("steak")) {
			knife = new SteakKnife();
		}
		else if (knifeType.compare("chefs")) {
			knife = new ChefsKnife();
		}
		return knife;
	}
};

 class KnifeStore {
 private :
	 KnifeFactory factory;
	// require a KnifeFactory object to be passed
	// to this constructor:
 public:
	 KnifeStore(KnifeFactory f) :factory(f) {}
		
	Knife* orderKnife(std::string knifeType) {
		Knife *knife;
		//use the create method in the factory
		knife = factory.createKnife(knifeType);
		//prepare the Knife
		knife->sharpen();
		knife->polish();
		knife->package();
		return knife;
	}
};