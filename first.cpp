// C++ Program to calculate the sum of first N natural
// numbers using recursion
#include <iostream>
#include <math.h>
#include <stdio.h>
// #include <thread>

using namespace std;
  
int nSum(int n)
{
    // base condition to terminate the recursion when N = 0
    if (n == 0) {
        return 1;
    }  
    // recursive case / recursive call
    int res = n * nSum(n - 1);  
    return res;
}
int fibonacci(int n) {
    if (n <= 1)
        return n;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}

  
int main()
{
    int n = 5;  
    // calling the function
    int sum = nSum(n);  
    cout << "Sum = " << sum << std::endl;

    printf("%d\n",fibonacci(6));
    cout << fibonacci(6) << std::endl;

    // while(1){
    //     std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // }
    return 0;
}





