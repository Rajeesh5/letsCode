#include<iostream>
#include<list>
#include<algorithm>


using namespace std;




void removeDuplicatefromList(list<int>& lst) {

	// { 1, 1, 1, 2, 2, 3, 4, 4, 5, 6, 6, 6  } =>
	// list become { 1, 2, 3, 4, 5, 6 }


	auto i = lst.begin();
	auto next = lst.begin();
	
	while (i != lst.end()) {

		// Iterate next pointer till match  
		while (( next != lst.end() ) && ( *i == *next )) {
			next++;
		}
		
		// why ++i, because need to keep first occurence of element
		// after delete need to update i.
		i = lst.erase(++i, next);

	}
}


void collapseList(list<int>& lst) {


	// lst   { 1, 2, 2, 1, 5, 3, 4, 4, 3, 6, 6 ,7 }
	// =>    { 1, 1, 5, 3, 4, 4, 3, 6, 6, 7 }
	// =>    { 5, 3, 4, 4, 3, 6, 6, 7 }
	// =>    { 5, 3, 3, 6, 6, 7 }
	// =>    { 5, 6, 6, 7 }
	// OP    { 5, 7 }

	auto iter = lst.begin();
	auto next = lst.begin();
	auto prev = lst.begin();

	while (iter != lst.end()) {

		next++;
		
		//if (prev != lst.begin()) {
		//	prev--;
		//}
		
		if ((next != lst.end()) && (*next == *iter)) {

			lst.erase(iter);			// collapse first item.
		
			if (prev == lst.begin()) {
				iter = std::next(next , 1);
				prev = iter;
			}
			else {
				iter = prev;
			}


			lst.erase(next);     // collapse second item.

		}
		else {
			iter++;
			prev++;
		}


	}


}

void displayList(list<int>& lst) {

	for (auto ele : lst) {
		cout << ele << " ";
	}
	cout << endl;

}



int main() {

	list<int> lst = { 1,1,4,5,6,6,6,2,2,3,4,1 };
	
	lst.sort();

	// Cant use std::sort(), need random access iterator.
	// std::sort(lst.begin(), lst.end(),greater<int>());
	
	displayList(lst);

	removeDuplicatefromList(lst);
	displayList(lst);

	removeDuplicatefromList(lst);
	displayList(lst);
	

	lst.erase(lst.begin(),lst.end());

	lst = { 1, 2, 2, 1, 5, 3, 4, 4, 3, 6, 6 ,7 };

	collapseList(lst);
	displayList(lst);


	return 0;
};