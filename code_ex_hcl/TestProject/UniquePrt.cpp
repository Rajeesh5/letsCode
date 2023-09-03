
#include<iostream>
#include<memory>


struct Data {
	int int_part;
	char char_part;
	Data(int z, char ch) :int_part(z), char_part(ch) {}
	void reset() { int_part = 0; char_part = '\0'; }
	void showData() {

		if (int_part == NULL) {
			std::cout << "0" << std::endl;
		}
		else {
			std::cout << int_part << std::endl;
		}
		std::cout << int_part << std::endl;
		if (char_part == '\0') {
			std::cout << "NULL" << std::endl;
		}
		else {
			std::cout << char_part << std::endl;
		}
	}
};



template < class T>
class UniquePtr {

public:
	explicit UniquePtr(T* ptr=0) :pointee(ptr) {}

	T* operator -> () const;

	UniquePtr(UniquePtr<T>&& rhs)  noexcept{
		this->pointee = rhs.pointee;
		rhs.pointee = nullptr;
	}

	UniquePtr& operator = (UniquePtr<T>&& rhs) {
		if (*this == rhs) {
			return *this;
		}
		this->pointee = rhs.pointee;
		rhs.pointee = nullptr;
	}


	~UniquePtr() {
		if (pointee) {
			delete pointee;
			pointee = nullptr;
		}
	}

private:
	UniquePtr& operator = ( const UniquePtr<T>&) =delete;
	UniquePtr(const UniquePtr<T>&) =delete;
	T* pointee;
};

template<class T>
inline T* UniquePtr<T>::operator->() const
{
	return pointee;
}

int main() {

	UniquePtr <Data> ptr1(new Data(65,'A'));
	ptr1->showData();
	UniquePtr <Data>ptr2(std::move(ptr1));
	ptr2->showData();
	UniquePtr <Data>ptr3 = std::move(ptr2);
	ptr3->showData();


}
	
