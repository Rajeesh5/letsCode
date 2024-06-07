#include "person.hpp"
#include <iostream>
#include <vector>
#include <memory>

class Collection {
public:
	void AddPeople(std::shared_ptr<Person> p){
		collection_.emplace_back(p);
	}
	~Collection () { 
		collection_.clear();
		std::cout << "Collection Distroyed" << std::endl;  
	}

private:
	std::vector<std::shared_ptr<Person>> collection_;		
};

int main() {

	//AStart scope
	{

		auto collection_ptr = std::make_unique<Collection>();
		
		auto p1 = std::make_shared<Person>(35,"Rajeev");
		auto p2 = std::make_shared<Person>(36,"RohanK");
		auto p3 = std::make_shared<Person>(37,"MohanK");
		

		collection_ptr->AddPeople(p1);
		collection_ptr->AddPeople(p2);
		collection_ptr->AddPeople(p3);

	}
	return 0;
}
