#include<iostream>

/*
class Bird {
public:
    virtual void eat() = 0;
    virtual void fly() = 0;
    virtual void Walk() = 0;
};

class Dove : public Bird {
    //Dove can eat,fly,walk
    void eat() {}
    void fly() {}
    void Walk() {}
};

class Penguin : public Bird {
    //But Penguin cant fly.
    void eat() {}
    void fly() {}
    void Walk() {}
};

*/
//Correct Design is::

class Bird {
public:
    virtual void eat() = 0;   //Because evey bird can eat, common property
};

class FlyingBirds : public Bird {
public:
    //FlyingBirds can eat,fly,walk    
    void fly() {}
    void Walk() {}
    void eat() {}
};

class NonFlyingBirds : public Bird {
public:
    //But Penguin cant fly.
    void eat() {}
    void Walk() {}
};


// Note::
// LSP definamtion- Function that use pointers or ref to base classess must be
//                  able to use object of derived class without knowing it.   

void LovelyBird(Bird* bird) {
    std::cout << "Lovly bird can eat\n";
    // There is no scope to make bird fly. 
    //bird->fly();
}

int main_LSP() {
    Bird* dove = new FlyingBirds();
    LovelyBird(dove);

    Bird* penguin = new NonFlyingBirds();
    LovelyBird(penguin);  // But we know that Penguin cant fly

	return 0;
}