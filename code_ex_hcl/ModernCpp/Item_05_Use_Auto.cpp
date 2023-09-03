#include<unordered_map>

using namespace std;


int main() {

	std::unordered_map<std::string, int> PinCode;

	PinCode.insert(std::make_pair<string, int>("Balumath", 829202));
	PinCode.insert(std::make_pair<string, int>("Chandva",  829203));
	PinCode.insert(std::make_pair<string, int>("Kuru",     829204));
	PinCode.insert(std::make_pair<string, int>("Ranchi",   829205));


	for (std::pair<const std::string, int>& place : PinCode) {
	
	//for (auto &place : PinCode) {
		if (place.first == "Kuru") {
			place.second = 123654;
		}
	}

	return 0;
}
