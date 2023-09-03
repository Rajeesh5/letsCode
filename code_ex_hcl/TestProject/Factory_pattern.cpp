#include<iostream>

using namespace std;

class Knife {
public:
	virtual void sharpen() = 0;
	virtual void polish() = 0;
	virtual void package() = 0;
};

class BudgetHomeKnife : public Knife {
	virtual void sharpen() override{}
	virtual void polish() override {}
	virtual void package() override {}
};

class BudgetChefsKnife : public Knife {
	virtual void sharpen() override {}
	virtual void polish() override {}
	virtual void package() override {}
};

class IndianArmyKnife:public Knife {
	virtual void sharpen() override {}
	virtual void polish() override {}
	virtual void package() override {}
};

class SwissArmyKnife :public Knife {
	virtual void sharpen() override {}
	virtual void polish() override {}
	virtual void package() override {}
};


class KnifeStore {
public:
	Knife* orderKnife(string knifeType) {

		Knife* knife = createKnife(knifeType);
		knife->sharpen();
		knife->polish();
		knife->package();
		return knife;
	}
	virtual Knife* createKnife(string type) = 0;
};

class BudgetKnifeStore :public KnifeStore {
public:

	virtual Knife* createKnife(string knifeType) override {
		if (knifeType.compare("home")==0) {
			return new BudgetHomeKnife();
		}
		else if (knifeType.compare("chefs")==0) {
			return new BudgetChefsKnife();
		}
		//.. more types
		else return nullptr;
	}
};

class ArmyKnifeStore :public KnifeStore {
public:
	virtual Knife* createKnife(string knifeType) override {
		if (knifeType.compare("IndianArmy") == 0) {
			return new IndianArmyKnife();
		}
		else if (knifeType.compare("SwissArmy") == 0) {
			return new SwissArmyKnife();
		}
		//.. more types
		else return nullptr;
	}
};


int main() {

	KnifeStore *store = new BudgetKnifeStore();

	Knife* budgetHomeKnife = store->createKnife("home");
	budgetHomeKnife->sharpen();
	budgetHomeKnife->polish();
	budgetHomeKnife->package();

	delete store;
	store = nullptr;
	
	store = new ArmyKnifeStore();
	Knife* budgetHomeKnife = store->createKnife("SwissArmy");
	budgetHomeKnife->sharpen();
	budgetHomeKnife->polish();
	budgetHomeKnife->package();


	return 0;
}


