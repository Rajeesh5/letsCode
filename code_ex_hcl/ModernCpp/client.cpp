#include "Widget.h"

int main() {

	
	Widget w1;				// Copy - operation
	Widget w2(w1);
	Widget w3;
	w3 = w1;
	
	Widget w4(std::move(w1));  // Move - operation
	Widget w5;
	w5 = std::move(w3);

	return 0;
}