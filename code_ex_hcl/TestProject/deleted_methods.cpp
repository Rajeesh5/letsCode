#include<iostream>
#include<map>

using namespace std;

class Magic {
public:
	Magic() = default;						// explicit let compiler use default constructor
	Magic& operator=(const Magic&) = delete; // explicit declare refuse constructor
	Magic(int magic_number) :num(magic_number) {}
private:
	int num;
};


template <typename Key, typename Value, typename F>
void update(std::map<Key, Value>& m, F foo) {
	// TODO:
}


int main() {

	Magic m1(100), m2(200);


	std::map<std::string, long long int> m{
			{"a", 1},
			{"b", 2},
			{"c", 3}
	};


	update(m, [](std::string key) {
		return std::hash<std::string>{}(key);
		});

	//for (auto&& [key, value] : m)
	//	std::cout << key << ":" << value << std::endl;
	
}

