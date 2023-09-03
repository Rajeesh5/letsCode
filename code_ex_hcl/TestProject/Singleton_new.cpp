#include <iostream>

using namespace std;

class singleton
{
public:
	static singleton* getInstance();

private:
	singleton() {}
	const singleton& operator=(const singleton&) = delete;
	static singleton* instance;
};

singleton* singleton::instance = 0;

singleton* singleton::getInstance()
{
	if (!instance) {
		instance = new singleton();
		cout << "getInstance(): First instance\n";
		return instance;
	}
	else {
		cout << "getInstance(): previous instance\n";
		return instance;
	}
}

int main()
{
	singleton* s1 = singleton::getInstance();
	singleton* s2 = singleton::getInstance();
	
	
	
	return 0;
}

