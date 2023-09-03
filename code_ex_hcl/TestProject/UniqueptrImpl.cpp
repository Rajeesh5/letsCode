#include<iostream>

using namespace std;


template<typename T>
class UniquePtr {
public:
	UniquePtr():m_pObject(nullptr){}
	UniquePtr(T* pointee) :m_pObject(pointee){}
	
	// Move c'tor
	UniquePtr(UniquePtr<T>&& rhs)  noexcept{
		// Transfer ownership of the memory pointed by dyingObj to this object
		m_pObject = std::move(rhs.m_pObject);
		rhs.m_pObject = nullptr;
	}

	// Move assigment
	UniquePtr<T>& operator = (UniquePtr<T>&& rhs) {
		
		// Cleanup existing data.
		this->~UniquePtr();
		
		// Transfer ownership of the memory pointed by dyingObj to this object
		m_pObject = std::move(rhs.m_pObject);
		rhs.m_pObject = nullptr;
		return *this;
	}

	T* operator ->()const { return m_pObject; }
	T& operator * ()const { return *m_pObject; }

	~UniquePtr() { 
		if(m_pObject)
		delete m_pObject; 
	}

	UniquePtr(const UniquePtr<T>&) = delete;
	UniquePtr<T>& operator = (UniquePtr <T>&) = delete;

private:

	T* m_pObject;
};


class Widget {
	std::string name;
public:
	Widget(const string& nm) :name(nm) {}
	std::string getName() { return name; }
};


int main() {

	UniquePtr<Widget> uptr1(new Widget("Mouse"));
	UniquePtr<Widget> uptr2(std::move(uptr1));			// Move c'tor
	UniquePtr<Widget> uptr3;
	uptr3 = std::move(uptr2);

	cout << uptr1->getName() << endl;;
	cout << uptr3->getName() << endl;;

	return 0;
}

