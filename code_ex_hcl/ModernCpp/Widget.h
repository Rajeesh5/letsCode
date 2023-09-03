#include<iostream>


class Widget { 											// in "widget.h"
public:
	
	// Construction & distruction 
	Widget();
	~Widget();
	
	// Copy Operation
	Widget(const Widget& rhs); 							
	Widget& operator=(const Widget& rhs); 				

	// Move Operatation.
	Widget(Widget&& rhs);
	Widget& operator=(Widget&& rhs);

private:
	struct Impl;
	std::unique_ptr<Impl> pImpl; 						// use smart pointer
};

