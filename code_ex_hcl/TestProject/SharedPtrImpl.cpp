#include<iostream>

using namespace std;

/* Reference Count: A simple class for maanging the number of active smart pointers*/
class ReferenceCount
{
private:
    int m_RefCount{ 0 };
public:
    void Increment()     {        ++m_RefCount;  }
    void Decrement()     {        --m_RefCount;  }
    int GetCount() const {   return m_RefCount;  }
};

template<typename T>
class SmartPtr {
public:
    // Default assigment.
    SmartPtr():m_pRCnt(nullptr), m_pObject(nullptr){}

    // Parameterized c'tor
    SmartPtr(T* object) :m_pObject(object), m_pRCnt(new ReferenceCount()) {
        m_pRCnt->Increment();
        cout << "Created smart_ptr! Ref count is " << m_pRCnt->GetCount() << endl;
    }

    // Copy c'tor
    SmartPtr(const SmartPtr<T>& object):m_pObject(object.m_pObject),m_pRCnt(object.m_pRCnt) {
        m_pRCnt->Increment();
        cout << "Copied smart_ptr! Ref count is " << m_pRCnt->GetCount() << endl;
    }

    // Assigment Overload.
    SmartPtr<T>& operator = (SmartPtr<T>& rhs) {
        // Check for self assigment.
        if (this == &rhs) {
            return *this;
        }

        // Decrement the ref_cnt of LHS
        if (m_pRCnt) {
            m_pRCnt->Decrement();
            // Delete if ref_cnt of LHS = 0
            if (m_pRCnt->GetCount() == 0) {
                delete m_pRCnt;
                delete m_pObject;
            }
        }

        // Copy RHS Data to LHS and increase the ref_cnt 
        m_pObject = rhs.m_pObject;
        m_pRCnt = rhs.m_pRCnt;
        m_pRCnt->Increment();

        return *this;
    }
    
    // Member Access operator overload
    T* operator ->()const { return m_pObject; }
    // Derefrencing operator overload
    T& operator *() const { return *m_pObject; }

    // Test for null-ness and convert smart_ptr to dumb_ptr
    operator T* () { return m_pObject; }

    void reset() {    
        m_pRCnt->m_RefCount = 0;
        delete m_pObject;
        m_pObject = nullptr;
    }

    // D'cot
    virtual ~SmartPtr() {
        if (m_pRCnt->GetCount() > 0) {            
            cout << "Destroyed smart_ptr! Ref count is " << m_pRCnt->GetCount() << endl;
            m_pRCnt->Decrement();
            // Delete only if ref_cnt = 0
            if (m_pRCnt->GetCount() <= 0) {
                delete m_pObject;
                delete m_pRCnt;
                m_pObject = nullptr;
                m_pRCnt = nullptr;
            }
        }    
    }
    
    void use_count() {
        cout << "Ref_cnt = " << m_pRCnt->GetCount() << endl;
    }

private:
    T* m_pObject;
    ReferenceCount* m_pRCnt;
};

class Widget {
    std::string name;
public:
    Widget(const string &nm):name(nm){}
    std::string getName() { return name; }
};


int main() {

    SmartPtr<Widget> sw1(new Widget("Apple Watch"));    // ref_cnt = 1
    SmartPtr<Widget> sw2(sw1);                          // copy c'tor, ref_cnt = 2
    SmartPtr<Widget> sw3(sw2);                          // copy c'tor, ref_cnt = 3

    cout << sw3->getName() << endl;
    
    sw1.use_count();          // ref_cnt = 3
    sw2.use_count();          // ref_cnt = 3
    sw3.use_count();          // ref_cnt = 3

    SmartPtr<Widget> sw4(new Widget("Laptop"));         // sw4 ref_cnt = 1
    SmartPtr<Widget> sw5(sw4);                          // sw5 ref_cnt = 2  

    sw4.use_count();          // ref_cnt = 2
    sw5.use_count();          // ref_cnt = 2
    
    sw5 = sw5;                                          // Self assigment check.
    sw3 = sw5;                                          // sw3 ref_cnt = 3    

    sw3.use_count();          // ref_cnt = 3
    sw5.use_count();          // ref_cnt = 3
    
    SmartPtr<Widget> sw6;
    sw6 = sw5;                                          // sw6 ref_cnt = 4    

    sw5.use_count();          // ref_cnt = 4
    sw6.use_count();          // ref_cnt = 4

    Widget *ptr = sw5;        // converting smart_ptr to dump
    // delete ptr;            // this is pure Devil


    //null-ness checking..
    if (sw5){}
    if (sw5 == nullptr) {}
    if (!sw5) {}

    return 0;
}