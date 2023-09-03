#include<iostream>
#include<ctime>


using namespace std;

// Bsae abstract class

class Person {                           
public:
	
	Person(const int age, const char* name) :m_age(age), m_pName(theName(name)) {}
	Person(const Person& rhs) :m_age(rhs.m_age), m_pName(rhs.m_pName) {}
	
	Person& operator = (const Person&);

	inline char* GetName() { return m_pName; }
	inline int GetAge() { return m_age; }
	virtual void PrintDetails() = 0;	// Pure virtual function.

	virtual ~Person() { delete m_pName; }
protected:
	int m_age;
	char* m_pName;	
private:
	 char* theName(const char* name){
		 char* temp = nullptr;
		 if (name != NULL) {
			 const size_t lenght = strlen(name);
			 temp = new char[lenght+1];
			 memcpy(temp, name, lenght);
			 temp[lenght] = '\0';
		 }
		 return temp;
	 }
};

Person& Person::operator= (const Person& rhs) {
	if (this == &rhs) return *this;

	this->m_age = rhs.m_age;
	this->m_pName = rhs.m_pName;
	return *this;
}



class EmployeementData{
public:
	
	void PrintDetails() {
		std::cout << "\n----------EmployementData----------\n";
		std::cout << "Oragenazation Name: " << m_orgName << endl;
		std::cout << "Current CTC       : " << m_salary  << endl;
		std::cout << "Date Of Joining   : " << ctime(&m_DOJ) << endl;
	}
	static EmployeementData* GenrateEmpData(const std::string name, double salary){		
		EmployeementData* eData = new EmployeementData(name, salary);
		return eData;
	}
private:
	EmployeementData(const std::string name, double salary) :m_orgName(name), m_salary(salary), m_DOJ(time(0)) {}
	EmployeementData(EmployeementData&) = delete;
	EmployeementData& operator = (EmployeementData&) = delete;
	std::string m_orgName;
	double m_salary;
	time_t m_DOJ;
};


class Employee : public Person{

public:
	char* GetName() { return m_pName; }
	int GetAge() { return m_age; }
	Employee(const int age, const char* name, EmployeementData *eData) :Person(age, name),m_pdata(eData) {	}

	void PrintDetails() {
		m_pdata->PrintDetails();
		std::cout << "\n----------Employee Data----------\n";
		std::cout << "Name      : " << this->GetName() << endl;
		std::cout << "Age       : " << this->GetAge() << endl;
	}

private:
	EmployeementData* m_pdata;
};

int main() {

	EmployeementData* edata = EmployeementData::GenrateEmpData("XYZ.corp", 800000000.00);
	Employee e1(36, "Mr. Kumar Sharma", edata);
	e1.PrintDetails();

	delete edata;
	return 0;
}

