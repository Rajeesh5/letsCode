#include<iostream>
#include<type_traits>


void algorithm_signed(int i) {
	/* algorithms works for signed interger well*/
}

void algorithm_unsigned(unsigned u) {
	/* algorithms works for unsigned interger well*/
}

// the template function algorithm acts as a dispatcher : 
// when instantiated, the compiler will grab the right 
// function according to the type T passed in.

template <typename type>
void algorithm(type t)
{
	if constexpr (std::is_signed<type>::value)
		algorithm_signed(t);
	else if constexpr (std::is_unsigned<type>::value)
		algorithm_unsigned(t);
	else
		static_assert(std::is_signed<type>::value || std::is_unsigned<type>::value, "Must be signed or unsigned!");
}

int main() {

	algorithm(3);       // T is int, include algorithm_signed()

	unsigned x = 3;
	algorithm(x);       // T is unsigned int, include algorithm_unsigned()

	// algorithm("hello"); // T is string, build error!

	return 0;
}







