#include "singlton.hpp"
#include <iostream>

class AnySingletonUser {
    public:
    void MemberFunction();
    void AnotherMemberFunction();
};


void AnySingletonUser::MemberFunction() {
    std::string result = Singleton::getInstance().doThis();
    std::cout << result << std::endl;
}
void AnySingletonUser::AnotherMemberFunction() {
    int result = Singleton::getInstance().doSomething();
    std::cout << result << std::endl;
}

int main() {
    
    AnySingletonUser object;
    object.AnotherMemberFunction();
    object.MemberFunction();

    return 0;

}



