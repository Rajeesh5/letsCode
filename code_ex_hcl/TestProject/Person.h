#pragma once
#include<string>
#include<iostream>



// The class person depend upon decleration of other class rater then 
// Depend on defination/implementation.

// fwd declerations are enough to support parameter types, dont need to
// include "date.h" or "address.h"
class Date;				
class Address;


class Person {
public:

	// Rule of 6:: Disctuctor + Move cons't + Copy cons't + Default cons't.
	// Note that:: All the member function declared only.
	//             Implementation goes into Person.cpp file.

	Person(const std::string& name, const Date& birthday, const Address& addr);
	Person();

	//	Must need to declear & define the distructor, otherwise compile give errors:
	//	1.	use of undefined type 'Person::PersonPimpl'
	//	2.  and can’t delete incomplete type.
	// Why ?? More details in Modern C++ Item-22 (PIMPL) 

	~Person();
	
	// As the rule of special function, declaration of a destructor in Widget 
	// prevents compilers from generating the move operations.

	Person(Person&& rhs) noexcept;
	Person& operator =(Person&& rhs) noexcept;

	// Since Move Cons't declered, so complier dont genrate copy operation. 
	Person(const Person& rhs);
	Person& operator =(const Person& rhs);



	//***Start***//
	// Methods for Class Person.
	// Make sure PersonPimpl has same function like Person has.
	// And using deligation Person class deligate call into 
	// Real implimentaion of PersonPimpl class.

	std::string GetName() const;
	std::string GetBirthDate();
	std::string GetAddress();
	//****End****//

private:
	class PersonPimpl;
	std::unique_ptr<PersonPimpl> m_pRealPerson;
	// PersonPimpl* mp_RealPerson;      // Prefer to use smart_ptr over raw pointer. 
	
	/*
	std::string theName; 				// implementation detail
	Date theBirthDate; 					// implementation detail
	Address theAddress; 				// implementation detail
	*/

};
