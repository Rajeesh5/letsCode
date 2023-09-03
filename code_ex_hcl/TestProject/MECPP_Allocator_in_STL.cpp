#include<iostream>
#include<vector>
#include<map>


// Even we can create our won allocator class to perform
// low level opertaion. Better to extend our custom class 
// to std::allocator for reuse functionality.


template<typename type>
class MyAlloc1 : public std::allocator<type> {
	// Put it blank, to reuse methods of std::allocator
};

template<typename type>
class MyAlloc2 : public std::allocator<type> {
public:
	type* allocate(size_t size) {
		std::cout << "Allocation request size => " << size << std::endl;
		return new type[size];
	}

	void dealocate(type* ptr, size_t size) {
		std::cout << "De_Allocation request size => " << size << std::endl;
		delete[] ptr;
	}

};


// we know that how to create aliases with typedef 
// typedef std::string identifier_t;
// typedef std::map<int,int> mymap_t;

// But C++11 offers to create aliases with 'using' keywords
using identifier_t = std::string;
using mymap_t = std::map<int, int>;


template<typename type>
using vectorOfSet = std::vector<std::set<type>>;

vectorOfSet<int> vs;




int main() {

	// Note:: There is no diffrence between v1, v2 and v3, for v1 by-default 
	// allocator<int> passed.

	std::vector<int> v1;
	std::vector<int, std::allocator<int>> v2;
	std::vector<int, MyAlloc1<int>> v3;
	
	// using custom allocator.

	std::vector<int, MyAlloc2<int>> v4;
	v4.push_back(10);
	v4.push_back(20);
	v4.push_back(30);









	return 0;
}