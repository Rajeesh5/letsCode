
#include<iostream>




/*

class WidgetImpl {
public:
	WidgetImpl() :a(0), b(0), c(0) {}
	WidgetImpl(int x, int y, int z) :a(x), b(y), c(z) {}

	void ShowValue() {
		std::cout << "value1 " << a << std::endl;
		std::cout << "value2 " << b << std::endl;
		std::cout << "value3 " << c << std::endl;
	}
private:
	int a, b, c;
};

class Widget {
public:
	Widget(int x, int y, int z) {
		impl = new WidgetImpl(x, y, z);
	}

	Widget(const Widget& rhs) {
		impl = new WidgetImpl;
		impl = rhs.impl;
	}

	Widget& operator =(const Widget& rhs) {
		if (this == &rhs) return *this;
		delete impl;
		impl = new WidgetImpl;
		impl = rhs.impl;
		return *this;
	}

	~Widget() {
		delete impl;
	}

	void ShowValue() {
		impl->ShowValue();
	}
	
	void swap(Widget& other)
	{
		using std::swap;
		std::cout << "Inside member swap\n";
		swap(impl, other.impl);				// to swap Widgets, swap their
	}										// pImpl pointers
	
	
private:
	WidgetImpl* impl;
};

namespace std {
	template<>								// typical implementation of std::swap;
	void swap<Widget>(Widget& a, Widget& b) // swaps a’s and b’s values
	{
		cout << "Inside non-member std::swap Widget version\n";
		a.swap(b);
	}
}

*/


template<typename T>
class WidgetImpl {
public:
	WidgetImpl() :a(0), b(0), c(0) {}
	WidgetImpl(int x, int y, int z) :a(x), b(y), c(z) {}

	void ShowValue() {
		std::cout << "value1 " << a << std::endl;
		std::cout << "value2 " << b << std::endl;
		std::cout << "value3 " << c << std::endl;
	}
private:
	T a, b, c;
};

template<typename T>
class Widget {
public:
	Widget(T x, T y, T z) {
		impl = new WidgetImpl<T>(x, y, z);
	}

	Widget(const Widget<T>& rhs) {
		impl = new WidgetImpl;
		impl = rhs.impl;
	}

	Widget& operator =(const Widget<T>& rhs) {
		if (this == &rhs) return *this;
		delete impl;
		impl = new WidgetImpl<T>;
		impl = rhs.impl;
		return *this;
	}

	~Widget() {
		delete impl;
	}

	void ShowValue() {
		impl->ShowValue();
	}

	void swap(Widget& other)
	{
		using std::swap;
		std::cout << "Inside member swap\n";
		swap(impl, other.impl);				// to swap Widgets, swap their
	}										// pImpl pointers


private:
	WidgetImpl<T>* impl;
};

/*

namespace std {
	template<typename T>							 // typical implementation of std::swap;
	void swap<Widget<T>>(Widget<T>& a, Widget<T>& b) // swaps a’s and b’s values
	{
		cout << "Inside non-member std::swap Widget version\n";
		a.swap(b);
	}
}

*/

template<typename T>
void swap(Widget<T>& a, Widget<T>& b) // swaps a’s and b’s values
{
	std::cout << "Inside non-member std::swap Widget version\n";
	a.swap(b);
}


int main() {


	/*
	Widget w1(10, 20, 30), w2(100, 200, 300);
	//w1 = w2;
	//w1.ShowValue();
	//w2.ShowValue();

	std::swap(w1,w2);

	w1.ShowValue();
	w2.ShowValue();
	*/


	Widget<int> w1(10, 20, 30), w2(100, 200, 300);
	w1 = w2;

	w1.ShowValue();


	return 0;
}


