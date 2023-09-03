#include<iostream>

class Investment {
public:
	bool isTaxable() { return true; };
};

Investment* createInvestment() { return NULL; };	//factory method.

int noOfDaysHeld(Investment* invest) {
	return 0;
}

int main_ECC_15() {

	std::shared_ptr<Investment> pInvest(createInvestment());
	int days = noOfDaysHeld(pInvest.get());         //get() convert Explicitly auto/share_ptr to row pointer.
	
	if (pInvest.get()->isTaxable()) {				//Explicite conversion..
	//...
	}


	// shared_ptrand auto_ptr also overload the pointer dereferencing operators(operator-> and operator*), 
	// and this allows implicit conversion to the underlying raw pointers :


	if ((*pInvest).isTaxable()) {   //Implicit conversion using operator * 
		//...
	}
	if (pInvest->isTaxable()) {		//Implicit conversion using operator ->
		//...
	}

	return 0;
}
