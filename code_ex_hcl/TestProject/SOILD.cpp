/*
// Two resposibilities: Connection Management + Data Communic
class Modem {
public:
	void dial(string pno);
	void hangup();
	void send(char c);
	char recv();
};

// Separate into two interfaces
class DataChannel {
public:
	void send(char c);
	char recv();
}
class Connection {
public:
	void dial(String phn);
	char hangup();
}
*/


class Employee {

public:
	double calculateBonus() {
		return m_salary * 0.7;
	}
private:
	// member_data;
};

class Employee {

public:
	double calculateBonus(string type) {
		if (type == "Parmanent")
			return m_salary * 0.7;
		else if (type == "Contract")
			return m_salary * 0.5;
		else return 0;
	}
private:
	string type;
};
