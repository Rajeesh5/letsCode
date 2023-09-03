#include<iostream>
#include<map>
#include<vector>

using namespace std;

class Dog {
	weak_ptr<Dog> m_pFriend;
	string m_name;
public:
	Dog(string name) {
		cout << "Dog is created: " << name.c_str() << endl;
		m_name = name;
	}
	~Dog() { cout << "dog is destroyed: " << m_name.c_str() << endl; }


	void makeFriend(shared_ptr<Dog> &f) { m_pFriend = f; }
	void bark() { cout << "Dog " << m_name.c_str() << " rules!" << endl; }
    void showFriend() {
        if (!m_pFriend.expired()) {
            cout <<"Me :" << m_name << " and My friend is: " << m_pFriend.lock()->m_name << endl;
            cout << "He is owned by: " << m_pFriend.use_count() << " pointers" << endl;
        }
    }
};


class Connection {
    //...
public:
    Connection() {}
};

class Sender {
    std::shared_ptr<Connection> connection;
public:
    Sender(shared_ptr<Connection> &con) :connection(con) {}
    void ConnectionUseCnt() { cout << connection.use_count() << endl; }
};


struct Observer {
    //...
    virtual void notify()=0;
};

struct Observed {
    //...
    void action() {
        //notify all observers
        for (auto& ob : observers)
            ob.get().notify();
    }
    std::vector<std::reference_wrapper<Observer>> observers;
};


struct Item {
    //...
};

struct Cache {

    auto getItem(int id) {

        std::shared_ptr<Item> ret;
        
        auto itr = itemsById.find(id);      //Search entry in the map
        if (itr != itemsById.end()) {
            ret = itr->second.lock();       // Found entry in the map
                                            // Try to acquire a shared_ptr<Item> 
                                            // from weak_ptr<Item>            
        }

        if (!ret) {
            // Either item is expired or entry is not found in the map.
            // Load fresh item from DB, initialize a shared_ptr,
            // and insert a weak_ptr in the map

            ret = std::make_shared<Item>();     //Initialize a shared_ptr     
            itemsById[id] = ret;                //Insert a weak_ptr in the map
        }         
        return ret;                             //Return the shared_ptr<Item>  
    }

    std::map<int, std::weak_ptr<Item>> itemsById; //Cache entries map
};


struct Client {
    // ...
    // The item is acquired from Cache
    std::shared_ptr<Item> item;
};



int main()
{
    /*
    {
		shared_ptr<Dog> pD1(new Dog("Gunner"));
		shared_ptr<Dog> pD2(new Dog("Smokey"));
		pD1->makeFriend(pD2);
		pD2->makeFriend(pD1);

        pD1->showFriend();
        pD2->showFriend();
	}//Memory Leak, no destructor called.

    */


    shared_ptr<Connection> con(new Connection());
    Sender s1(con);
    Sender s2(con);
    Sender s3(con);
    Sender s4(con);

    s1.ConnectionUseCnt();
    s4.ConnectionUseCnt();



    /*

     std::cout << std::boolalpha << std::endl;

     auto sharedPtr = std::make_shared<int>(2011);
     std::weak_ptr<int> weakPtr(sharedPtr);

     std::cout << "weakPtr.use_count(): " << weakPtr.use_count() << std::endl;
     std::cout << "sharedPtr.use_count(): " << sharedPtr.use_count() << std::endl;
     std::cout << "weakPtr.expired(): " << weakPtr.expired() << std::endl;

     if (std::shared_ptr<int> sharedPtr1 = weakPtr.lock()) {
         std::cout << "*sharedPtr: " << *sharedPtr << std::endl;
         std::cout << "sharedPtr1.use_count(): " << sharedPtr1.use_count() << std::endl;
     }
     else {
         std::cout << "Don't get the resource!" << std::endl;
     }

     weakPtr.reset();

     if (std::shared_ptr<int> sharedPtr1 = weakPtr.lock()) {
         std::cout << "*sharedPtr: " << *sharedPtr << std::endl;
         std::cout << "sharedPtr1.use_count(): " << sharedPtr1.use_count() << std::endl;
     }
     else {
         std::cout << "Don't get the resource!" << std::endl;
     }

     std::cout << std::endl;


     unique_ptr<int> up = make_unique<int>(100);
     
     */

    /*
    auto sharedPtr = std::make_shared<int>(2011);
    std::weak_ptr<int> weakPtr(sharedPtr);

    cout << weakPtr.use_count() << endl;
    cout << sharedPtr.use_count() << endl;

    auto sharedPtr1 = weakPtr.lock();
    auto sharedPtr2 = weakPtr.lock();

    cout << sharedPtr1.use_count() << endl;
    cout << sharedPtr2.use_count() << endl;

    weakPtr.reset();


    cout << sharedPtr1.use_count() << endl;
    cout << sharedPtr2.use_count() << endl;

    auto sharedPtr3 = weakPtr.lock();
    cout << sharedPtr3.use_count() << endl;
    */
    return 0;
} 





