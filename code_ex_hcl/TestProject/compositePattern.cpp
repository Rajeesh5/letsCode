#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;



class IStructure {
public:
	virtual void enter() = 0;
	virtual void exit() = 0;
	virtual void location() = 0;
	virtual string getName() = 0;
};


class Housing : public IStructure {
	
public :

	Housing(string address):m_address(address) {
		m_structures.reserve(10);
		
	}
	string getName() {
		return m_address;
	}
	int addStructure(IStructure *component) {
		m_structures.push_back(component);
		return m_structures.size() - 1;
	}
	IStructure* getStructure(int componentNumber) {
		return m_structures.at(componentNumber);
	}
	void location() {
		cout << "You are currently in " << getName() << ". It has " << endl;
		for (auto structure : m_structures)
			structure->getName();	

		//for_each(m_structures.begin(), m_structures.end(), getName());
	}
	/* Print out when you enter and exit the building */
	void enter() { cout << "Enter into the building: " << getName() << endl; }
	void exit() { 
		cout << "Exit form the building: " << getName() << endl; 
	}

private:
	vector<IStructure*> m_structures;
	string m_address;
};

class Room : public IStructure {

public:
	Room(string name):m_name(name){}
	void enter() {
		cout << "You have entered the " << getName() << endl;
	}
	void exit() {
		cout << "You have left the " << getName() << endl;
	}
	void location() {
		cout << "You are currently in the " << getName() << endl;
	}
	string getName() {
		return m_name;
	}
private:
	string m_name;
};


int main_com() {
	
	Housing *building = new Housing("Shree Sai Apt, 9th Cross Celebrity Layout");
	Housing *floor1 = new Housing("123 Street - First Floor");	
	int firstFloor = building->addStructure(floor1);

	// 1BHK structure..
	Room *washroom = new Room("1F Washroom");
	Room *common= new Room("1F Common Area");
	Room* bedRoom = new Room("1F Common Area");

	int washRoomPos   = floor1->addStructure(washroom);
	int commonRoomPos = floor1->addStructure(common);
	int bedRoomPos   = floor1->addStructure(bedRoom);

	building->enter(); // Enter the building
	
	IStructure *currentFloor = building->getStructure(firstFloor);
	currentFloor->enter(); // Walk into the first floor

	
	IStructure* structure;
	
	// Walk into the wash room
	structure = dynamic_cast<Housing*>(currentFloor)->getStructure(washRoomPos);
	structure->enter(); 
	structure->location();
	structure->exit();
	
	// Walk into the common room
	structure = dynamic_cast<Housing*>(currentFloor)->getStructure(commonRoomPos);
	structure->enter();
	structure->location();
	structure->exit();

	// Walk into the men's room	
	structure = dynamic_cast<Housing*>(currentFloor)->getStructure(bedRoomPos);
	structure->enter();
	structure->location();
	structure->exit();

	return 0;

}