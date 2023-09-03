#include<iostream>

using namespace std;

class Widget {};

Widget CreateWidget() { return Widget(); }


int main() {

	Widget w;

	Widget&& w1 = w;	// Error!! w1 has Ravlue-ref which 
	                    // Cant be bound with w's Lvalue.

	auto&& w2 = w;      // Looks Like w2 has Rvalue-ref, but 
	                    // in reality with the type deduction auto
	                    // it become Universal-ref (Fwd-ref).
	// Note:: U-ref(fwd-ref) can easily bounded by Lvalue or Rvalue. 


	auto&& w3 = CreateWidget();



}