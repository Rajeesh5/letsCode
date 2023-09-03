#include<iostream>
#include<queue>

using namespace std;

class Meeting {
public:
	int start;
	int end;
	Meeting():start(0),end(0){	}
	Meeting(int x,int y):start(x),end(y){}
};

class PQMeetingCompare : public binary_function<Meeting, Meeting, bool> {
public:
	bool operator ()(const Meeting& lhs, const Meeting& rhs) {
		return lhs.end > rhs.end;
	}
};

void print_meeting(Meeting& meet) {
	cout << "[" << meet.start << " " << meet.end << "]" << endl;
}

void print_heap(priority_queue<Meeting,vector<Meeting>,PQMeetingCompare> var) {
	cout << "Printing Heap element" << endl;
	while (!var.empty()) {
		Meeting m = var.top();
		print_meeting(m);
		var.pop();
	}
}

int main() {

	vector<Meeting> meetings = { {2,6},{7,8},{8,10},{1,3},{9,15},{9,16} };

	sort(meetings.begin(), meetings.end(), [](const Meeting& x, const Meeting& y) {
		return x.start < y.start;
		});

	for_each(meetings.begin(), meetings.end(), print_meeting);

	priority_queue<Meeting, vector<Meeting>, PQMeetingCompare> minHeap;
	
	for (auto item : meetings) {
		minHeap.push(item);
	}

	
	print_heap(minHeap);

	

	return 0;

}  