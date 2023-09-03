
#include<iostream>

class Investment {};

Investment* createInvestment() { return NULL; };

void fun() {
	Investment* tmp = createInvestment();

	//...
	// What happen if exit pre-meturelly
	delete tmp;
		
	//•	Resources are acquiredand immediately turned over to resource - managing objects.
	//	The idea of using objects to manage resources is often called Resource Acquisition Is Initialization(RAII).
	//•	Resource - managing objects use their destructors to ensure that resources are released.

	std::auto_ptr<Investment> FD(createInvestment());
	std::auto_ptr<Investment> Equity = FD;           // Transfered the ownership to Equity, Now FD value is NULL;
	std::auto_ptr<Investment> othesr(Equity);        // Same as above.
	// Note::Resources managed by auto_ptrs must never have more than one auto_ptr pointing to them.
}

// Reference count based smart pointers

void f()
{
	// pInv1 points to the object returned from createInvestment

	std::shared_ptr<Investment> pInv1(createInvestment());
	std::shared_ptr<Investment> pInv2(pInv1);	// both pInv1 and pInv2 now
	                                                // point to the object.

	pInv1 = pInv2; 						// ditto — nothing has changed

} //pInv1 and pInv2 are destroyed, and the object they point to is automatically deleted.


// Note that both auto_ptr and shared_ptr uses delete not delete[] 
// That’s because vectorand string can almost always replace dynamically allocated arrays in c++.

std::auto_ptr<std::string> aps(new std::string[10]);		// bad idea! the wrong
										                    // delete form will be used
std::shared_ptr<int> spi(new int[1024]); 			        // same problem


