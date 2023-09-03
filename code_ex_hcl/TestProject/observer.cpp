#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


class Observer {
public:
	virtual void update(const string &) = 0;
};


// Users as a subscriber
class  Subscriber : public Observer {
	int m_id;
	std::string m_name;
public:
	Subscriber(const int id, const std::string &nm) :m_id(id),m_name(nm) {}
	virtual void update(const string &msg){
		cout << "Dear User:: " << m_name <<",  ";
		cout << "We have update for you..." << endl;
		cout << "\n-------------MSG-----------------\n";
		cout << msg << endl;
	}
};


class Subject {
public:
	virtual void RegisterObserver(Observer* observer) = 0;
	virtual void unregisterObserver(Observer* observer) = 0;
	virtual void notifySubscriber() = 0;
};


class Defect: public Subject {
private:
	vector<Observer*> observers;
	std::string m_notes;
	std::string m_defectId;
public:

	Defect(const std::string &id,const std::string &notes):m_defectId(id),m_notes(notes){}
	void RegisterObserver(Observer* observer) {
		observers.push_back(observer);
	}
	void unregisterObserver(Observer* observer) {
		observers.erase(std::remove(observers.begin(),observers.end(),observer),   observers.end());	
	}
	void notifySubscriber() {
		for (auto o : observers) {
			o->update(m_notes);
		}
	}

	void ChangeNotes(const std::string &new_text) {
		m_notes.append("\n---------\n");
		m_notes.append(new_text);
		notifySubscriber();
	}
};


int main_observer() {

	Defect defect("APAR0001", "UI defect");

	Subscriber s1(101, "Rajeev Sharma");
	Subscriber s2(102, "George A.");
	Subscriber s3(103, "Marlin D.");

	defect.RegisterObserver(&s1);
	defect.RegisterObserver(&s2);
	defect.RegisterObserver(&s3);

	defect.ChangeNotes("Developer comment:: Ready for code review");

	defect.unregisterObserver(&s2);

	defect.ChangeNotes("Reviewed and approve.");


}