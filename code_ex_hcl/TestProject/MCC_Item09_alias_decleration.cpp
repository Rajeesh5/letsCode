#include<iostream>




template< class T >                                 // (since C++11)
struct remove_reference;		                    

template< class T >                                 // (since C++14)
using remove_reference_t = typename remove_reference<T>::type;


template< class T > 
struct remove_reference { 
    typedef T type; 
};

template< class T > struct remove_reference<T&> { typedef T type; };
template< class T > struct remove_reference<T&&> { typedef T type; };






struct Point
{
    typedef double XCord;
    typedef double YCord;
};


template <typename T>
void foo(const T& t) {

    // declares a point to an object of type T::XCord, T::YCord    
     T::XCord  x;                                  // error (see text) why?
    // because the compiler does not know if T::XCord is a type or a value.    


    typename T::YCord y =0.0;                    // type of y is (T::YCord) 

    // Now the compiler knows for sure that T::YCord is a type, and will 
    // correctly make p a pointer to an object of that type.

}

int main()
{
    Point p;
    foo(p);
    return 0;
}




