#include<iostream>

using namespace std;

/*

class Widget {
public:
	Widget(int id):m_id(id){}
	int getID() { return m_id; }
	void setID(int id) { m_id = id; }
private:
	int m_id;
};

void Print1(std::unique_ptr<Widget> widget) {
	cout << "By Value" << widget->getID();
}

void Print2(std::unique_ptr<Widget>& widget) {
	cout << "By Ref" << widget->getID();
}

void Print3(Widget* widget) {
	cout << "By pointer" << widget->getID();
}

auto& UpdateWidget(unique_ptr<Widget>& widget) {
	// make some modification on widget then return. 
	widget->setID(99);
	return widget;				// Error, auto cant deduce the type of widget,
	                            // menas its refrence, need to return auto& or
	                            // use decltype(auto).
}

auto NewWidget1() {
	auto widget = make_unique<Widget>(100);
	return widget;		
}

auto NewWidget2() {
	return make_unique<Widget>(101);
}

*/













class Investment { 
public:
	virtual void MakeLogEntry() = 0;
	virtual ~Investment() = 0;			//Esential Design Componect.
};
class Stock : public Investment {
	//…
public:
	void MakeLogEntry() override {}

};
class Bond : public Investment {
	//…
public:
	void MakeLogEntry() override {}
};
class RealEstate : public Investment {
	//…
public:
	void MakeLogEntry() override {}
};

auto delInvestment = [](Investment* investment) {
	investment->MakeLogEntry();
	delete investment;
};


template<typename... Ts>										
std::unique_ptr<Investment, decltype(delInvestment)>	
makeInvestment(Ts&&... params)		
{
	std::unique_ptr<Investment, decltype(delInvestment)> pInv(nullptr, delInvestment);

	if ( /* a Stock object should be created */) {
		pInv.reset(new Stock(std::forward<Ts>(params)...));
	}
	else if ( /* a Bond object should be created */) {
		pInv.reset(new Bond(std::forward<Ts>(params)...));
	}
	else if ( /* a RealEstate object should be created */) {
		pInv.reset(new RealEstate(std::forward<Ts>(params)...));
	}
	return pInv;
}



int main() 
{
	/*
	auto widget = make_unique<Widget>(123);

	//Print1(widget);           // Error, Not possible, unique_ptr is not copiable
	Print2(widget);           // Still clint has its ownership.
	Print1(move(widget));     // Move the ownership to the Print1 of widgetlib 
	//Print3(widget);           // Error, use deleted CCTOR.

	auto widget1 = make_unique<Widget>(123);
	auto dev1    = UpdateWidget(widget1);         // Error, use deleted copy-c'tor
												  // If this complile, both widget1 and dev1 has 
	                                              // same ref of Widget (become share_ptr) 		
	auto dev1    = move(UpdateWidget(widget1));
	auto dev2    = NewWidget1();
	auto dev3    = NewWidget2();
	*/


	auto pInvestment = makeInvestment(arguments); 					// pInvestment is of type unique_ptr<Investment>

	return 0;
}