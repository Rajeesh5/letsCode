#include<iostream>
#include<mutex>
#include <atlstr.h>



using namespace std;

mutex m;

class Singleton {

public:
	static Singleton* GetInstance();

	void display() { cout << this << " Hi" << endl; }
private:
	Singleton() {}     // make is private not delete.	
	Singleton(const Singleton &){}
	
	const Singleton& operator=(const Singleton&) {};
	static Singleton* instance;
};

Singleton* Singleton::instance = nullptr;

Singleton* Singleton::GetInstance() {

	if (instance == nullptr) {
		unique_lock<mutex> ulock(m);
		if (instance == nullptr) {
			instance = new Singleton();   // If you delete defalut ctor 
		}								  // then how can use here.
		
	}
	return instance;
}

int main() {
	/*

	Singleton *s1 = Singleton::GetInstance();
	
	// Make copy ctr private and get rid below object creation.
	Singleton s2 = *s1;  
	Singleton s3(*s1);
	Singleton s4(s3);	
	
	Singleton* s2 = Singleton::GetInstance();   // still refreing same instance.

	// Make assigment operator private, to prohivate below.
	s2 = s3;   

	delete s1;
	*/

	CString sql = _T("update master_users set encrypted_password = '%s' where login_name = 'adam'");
	CString updSql;
	updSql.Format(sql, "aabc");

	cout << updSql << endl;

	updSql.Format(sql, "1234567890");

	cout << updSql << endl;

	return 0;

}