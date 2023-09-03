#include<iostream>
#include<ctime>
#include<vector>

class Customer {
	int customer_id;
	std::string customer_name;
public:
	int getID() { return customer_id; }
};

class Reservation {
	int reservation_id;
	time_t order_date_time;
	int order_customer_id;

public:
	void createReservation(Customer customer) {
		this->order_customer_id = customer.getID();
		this->order_date_time = current_date_time();
		this->reservation_id = craete_new_id();
	}
};


class CrewMember {};

class Airliner {
private:
	std::vector<CrewMember*> crew;
public:
	Airliner() {

	}
	void add(CrewMember *crewMember) {
		crew.push_back(crewMember);
	}
};




class Car {};
class ClientSubsystem {
	Sorting* m_pSort;
public:
	ClientSubsystem(Sorting* concreteSortingClass) {
		m_pSort = concreteSortingClass;
	}
	void sortInput(List customerList) {
		m_pSort->sort(customerList);
	}
};

class CarOwner : public Person {
public:
	CarOwner(Car& car) :m_pMyCar(&car) {}

	void DiverCar() {
		m_pMyCar->engin.start();
		//or m_PMyCar.getEngin().start();
	}
private:
	Car *m_pMyCar;
};

class Sample {
public:
	void N() {	}

};

class Test {
public:
	void M() {
		Sample sample;
		sample.N();
	}
};

