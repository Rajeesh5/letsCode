#include<iostream>

using namespace std;

class SortInterface {
public:
	virtual void sort(int arr[]) = 0;
};

class BubbleSort :public SortInterface {
	virtual void sort(int arr[]) override {
		// Do specific sort.
	}
};

class HeapSort :public SortInterface {
	virtual void sort(int arr[]) override {
		// Do specific sort.
	}
};

class ClientSorting {
public:
	ClientSorting() :m_startgy(nullptr) {}

	void doSort(int arr[]) {
		if (m_startgy) {
			m_startgy->sort(arr);
		}
	}
	void setStartgy(SortInterface* startgy) {
		if (m_startgy) {
			delete m_startgy;			
		}
		m_startgy = startgy;
	}

private:
	SortInterface* m_startgy;
};

int main() {

	int arr[] = { 12,36,96,89,69 };

	ClientSorting sort;
	BubbleSort* bsort = new BubbleSort();
	sort.setStartgy(bsort);
	sort.doSort(arr);


	HeapSort* hsort = new HeapSort();
	sort.setStartgy(hsort);
	sort.doSort(arr);

	return 0;

}