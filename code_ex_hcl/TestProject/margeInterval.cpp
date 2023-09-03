#include<iostream>
#include<vector>
#include<utility>

#include<algorithm>

using namespace std;

/*
class Interval {
public:
	Interval(int s,int e):m_start(s),m_end(e){}
private:
	int m_start;
	int m_end;
};
*/

typedef std::pair<int, int>Interval;
typedef std::vector<Interval> IntervalVector;

struct IntervalCompare : public binary_function<Interval, Interval, bool>
{
	bool operator ()(const Interval& lhs, const Interval& rhs) {
		return lhs.first < rhs.first;
	}
};

void print_interval(Interval& ival) {
	cout << ival.first << "->" << ival.second << endl;
}

void marge_interval(IntervalVector& arr) {

	Interval marged = { 0,0 };
	Interval a = *(arr.begin());									// store first element
	IntervalVector::iterator walker = arr.erase(arr.begin());       // remove first elem form interval arr
	

	while(walker != arr.end()) {                                    // Inerater thru end of the array.
		Interval b = *walker;

		if (a.second == b.first || a.second > b.first) {
			marged.first = a.first;
			marged.second = b.second;

			walker = arr.erase(walker);
			walker = arr.insert(walker, marged);
			walker++;
		}

		else if (a.second > b.second) {
			// a engulphing b completly.
			walker = arr.erase(walker);
			walker++;
		}
		else {

		}
	}
}

void erase_all(IntervalVector& interval_arr) {	
	IntervalVector::iterator walker = interval_arr.begin();

	// Imp: no post increment for walker, next location 
	//      updated by erase() method. 
	for (; walker != interval_arr.end(); ) {
		walker = interval_arr.erase(walker);
	}

}

int main() {	

	IntervalVector interval_arr;
	interval_arr.push_back(make_pair<int, int>(1, 4));
	//interval_arr.push_back(make_pair<int, int>(4, 8));
	interval_arr.push_back(make_pair<int, int>(7, 9));
	interval_arr.push_back(make_pair<int, int>(2, 5));


	sort(interval_arr.begin(), interval_arr.end(), IntervalCompare());

	// Remove duplicate, make sure no overlapping interval exists. 

	/*
	for_each(interval_arr.begin(), interval_arr.end(), print_interval);

	// binary_search, upper_bound, lower_bound
	if (binary_search(interval_arr.begin(), interval_arr.end(), make_pair<int,int>(2,5))){
		cout << "elemet exists\n";
	}
	*/


	marge_interval(interval_arr);

	
	
	
	erase_all(interval_arr);

	return 0;
}