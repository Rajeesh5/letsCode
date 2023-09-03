#pragma once
#include<string>

using namespace std;
struct Day {
	explicit Day(int d):val(d){}
	int GetVal() { return val; }
	int val;
};

struct Month {
	explicit Month(int m):val(m){}
	int GetVal() { return val; }
	int val;
};

struct Year {
	explicit Year(int y):val(y){}
	int GetVal() { return val; }
	int val;
};


class Date {
public:
	Date(const Day& day,const Month &month,const Year &year):
		m_day(day),m_month(month),m_year(year){}

	std::string GetDate(){
		return (to_string(m_day.GetVal()) + "-" +
			to_string(m_month.GetVal()) + "-" +
			to_string(m_year.GetVal()));
	                               
	}
private:
	Day		m_day;
	Month	m_month;
	Year	m_year;
		 
};
