#include<iostream>
#include<string>

using namespace std;
// User.h

/*

class RealUserImpl;
class User {
public:
    // ...
    User();
    ~User();
    void Login();
    void Logout();
private:
    
    RealUserImpl* m_pImpl; // warning!!! a raw pointer! :)
};

// User.cpp
class RealUserImpl
{
public:
    void DoLogin() { }
    void DoLogout() { }
private:
    string m_uname;
    string m_passwd;
};

User::User()
    : m_pImpl(new RealUserImpl())
{ }

User::~User() { delete m_pImpl; }

void User::Login() {
    m_pImpl->DoLogin();
}
void User::Logout() {
    m_pImpl->DoLogout();
}


*/




class RealUserImpl;
class User {
public:

    // Rule of 6: constructor, distructor, copy and move operation.
    explicit User() : m_pImpl(new RealUserImpl()) {};
    ~User() = default;

    User(const string& name, const string& pass){
        m_pImpl = make_unique<RealUserImpl>(name, pass);
    }
    // movable operation make it default, because unique_ptr is smart enough to 
    // hnadle below to operation.
    
    User(User&& rhs) noexcept = default;
    User& operator=(User&& rhs) noexcept = default;

    
    // Write own copy machnisum
    User(const User& rhs):m_pImpl( new RealUserImpl(*rhs.m_pImpl)){}
    User& operator=(const User& rhs) {
        if (this != &rhs) {
            m_pImpl.reset(new RealUserImpl(*rhs.m_pImpl));
        }
        return *this;
    }
    
    // Login Overload for const,non-const object.
    void Login()       {    Pimpl()->DoLogin(); };
    void Login() const {    Pimpl()->DoLogin(); };  

private:
    
    // In a const method this pointer will also become const which 
    // means we cannot assign a different value to it. 
    
    const RealUserImpl* Pimpl() const { return m_pImpl.get(); }
    RealUserImpl* Pimpl()             { return m_pImpl.get(); } 

    std::unique_ptr<RealUserImpl> m_pImpl;
};


class RealUserImpl {
public:
    RealUserImpl() = default;
    RealUserImpl(const string& nm, const string& pw) :
        m_name(nm), m_passwd(pw) {}
    RealUserImpl(std::unique_ptr<RealUserImpl>& uptr) :
        m_name(uptr->m_name), m_passwd(uptr->m_passwd) {}

    ~RealUserImpl() = default;

    void DoLogin();
    void DoLogin() const;
private:
    string m_name;
    string m_passwd;
};


void RealUserImpl::DoLogin() {
    // Actual Login Code..
    cout << "Login" << endl;
}

void RealUserImpl::DoLogin() const {
    // Actual Login Code..
    cout << "Const Login" << endl;
}




int main() {

    const User u1("Rajeev", "passwd");
    u1.Login();

    User u2(u1);
    u2.Login();

    User u3("George", "George");

    u2 = u3;

    return 0;
}