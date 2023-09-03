#include"Person.h"
#include"Address.h"
#include"Date.h"

// Real Implementation file.


class Person::PersonPimpl {

public:
	PersonPimpl(const std::string& name, const Date& birthday, const Address& addr):
		m_name(name),m_dob(birthday),m_address(addr){}



	std::string GetName() const		 {		return m_name; }
	std::string GetBirthDate()       {		return m_dob.GetDate(); };
	std::string GetAddress()     	 {		return m_address.GetAddress(); }

private:
	string	m_name;
	// However its good to have ref or pointer of Date & Address.
	// and create seperate decleration & implementation of Date & Address class.
	// this will further not to required includes header "date.h" & "address.h"

	// std::unique_ptr<DateImpl> m_upDOB;

	Date	m_dob;				
	Address m_address;	
};


Person::Person(const std::string& name, const Date& birthday, const Address& addr) :
	m_pRealPerson(std::make_unique<PersonPimpl>(name, birthday, addr)) {}


std::string Person::GetName() const { return m_pRealPerson->GetName(); };
std::string Person::GetBirthDate() { return m_pRealPerson->GetBirthDate(); }
std::string Person::GetAddress() { return m_pRealPerson->GetAddress(); }


// What the problem to making it default ? 
// -- Complier Error !! canot use deleted function.
// -- Shallow copy

// implement Person copy operations by calling Person::PersonPimpl 
// compiler - generated copy operations.

Person::Person(const Person& rhs): m_pRealPerson(std::make_unique<PersonPimpl>(*rhs.m_pRealPerson)) {}
Person& Person::operator =(const Person& rhs) { 
	*m_pRealPerson = *rhs.m_pRealPerson;
	return *this; 
}


// Default Implementations, taken care by unique_ptr

Person::Person() = default;
Person::Person(Person&& rhs) noexcept = default;
Person& Person:: operator =(Person&& rhs) noexcept = default;
Person::~Person() = default;



