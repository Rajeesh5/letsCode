#include"Widget.h"
#include"Gadget.h"
#include<vector>



struct Widget::Impl { 
	std::string name;
	std::vector<double> data;
	Gadget g1, g2, g3;
};

Widget::~Widget() {
	delete pImpl.get();
}

Widget::Widget() 										// create
	: pImpl(std::make_unique<Impl>()) 					// std::unique_ptr
{} 														// via std::make_unique


Widget::Widget(Widget&& rhs) = default; 				// Use default Implemenation.
Widget& Widget::operator=(Widget && rhs) = default;

Widget::Widget(const Widget& rhs)						// copy ctor
	: pImpl(std::make_unique<Impl>(*rhs.pImpl))
{}
Widget& Widget::operator=(const Widget& rhs) {			// copy operator=
	*pImpl = *rhs.pImpl;
	return *this;
}






