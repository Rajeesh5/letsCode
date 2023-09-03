#include "Person.h"
#include "Date.h"
#include "Address.h"


int main() {


	// Eirlier any chnages in implementation file need to recomplite the 
	// client. Now with PIMPL approch no need to recompile client


	Person p1("Rajeev Sharma", Date(Day(15), Month(01), Year(1986)),
		Address("Rajeev Sharma", "Bangalore", "ECity, Ph-01", 560100));


	Person p2("Neha Kumari", Date(Day(05), Month(03), Year(1993)),
		Address("Rajeev Sharma", "Bangalore", "ECity, Ph-01", 560100));


	p1 = std::move(p2);
	
	Person p3(p1);

	cout << p1.GetBirthDate() << endl;
	cout << p3.GetBirthDate() << endl;

	return 0;
}