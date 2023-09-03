
class Knife {
public:
	virtual void sharpen() = 0;
	virtual void polish() = 0;
	virtual void package() = 0;
};
class SteakKnife : public Knife {
	void sharpen() {}
	void polish() {}
	void package() {}
};
class ChefsKnife : public Knife {
	void sharpen() {}
	void polish() {}
	void package() {}

};

class KnifeFactory {
public:
	Knife* createKnife(std::string knifeType) {
		Knife* knife = nullptr;
		// create Knife object
		if (knifeType._Equal("steak")) {
			knife = new SteakKnife();
		}
		else if (knifeType._Equal("chefs")) {
			knife = new ChefsKnife();
		}
		return knife;
	}
};


class KnifeStore {
public:
	// require a KnifeFactory object to be passed
	// to this constructor:
	KnifeStore(KnifeFactory* factory) {
		this->m_pFactory = factory;
	}
	Knife* orderKnife(std::string knifeType) {
		//use the create method in the factory
		Knife* knife = m_pFactory->createKnife(knifeType);
		//prepare the Knife
		knife->sharpen();
		knife->polish();
		knife->package();
		return knife;
	}
private:
	KnifeFactory* m_pFactory;
};
