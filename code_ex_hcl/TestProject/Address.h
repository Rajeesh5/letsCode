#pragma once
#include<string>

using namespace std;

class Address {
public:
	Address(const string &name, const string &city, const string misc,long pin):
		m_name(name),m_city(city),m_misc(misc),m_pin(pin){}

	std::string GetAddress(){
		return (m_name + m_city + m_misc + to_string(m_pin));
	}

private:
	std::string m_name;
	std::string m_city;
	std::string m_misc;
	long		m_pin;

};
