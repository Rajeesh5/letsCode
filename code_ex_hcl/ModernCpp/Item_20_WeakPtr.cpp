#include<iostream>
#include<map>
using namespace std;

struct Item {
    int m_id;
    Item(int id):m_id(id){}
    void PrintItem() { cout << "Item_ID :: " << m_id << endl; }
};

class CacheImplementor {             
public:    
    std::shared_ptr<Item> FastLoadItem(int id);         // Fast Load with cache.  
private:
    std::shared_ptr<Item> LoadItem(int id);             // Factory Method.
    std::map<int, std::weak_ptr<Item>> m_ItemCache;     // Cache entries map.
};

std::shared_ptr<Item> CacheImplementor::FastLoadItem(int id)
{
    std::shared_ptr<Item> result;

    auto iter = m_ItemCache.find(id);      // Search entry in the map
    if (iter != m_ItemCache.end()) {       // Found entry in the map
        result = iter->second.lock();
        // Try to acquire a shared_ptr<Item> from weak_ptr<Item>            
    }
    if (!result) {
        // Either item is expired or entry is not found in the map.            
        // Load item form DB and update the cache.

        result = LoadItem(id);                   // Initialize a shared_ptr     
        m_ItemCache[id] = result;                  // Insert a weak_ptr in the map
    }
    return result;                               // Return the shared_ptr<Item>  
}

std::shared_ptr<Item> CacheImplementor::LoadItem(int id) {
    // Expensive operation, Load fresh item from Database.
    // ...
    return make_shared<Item>(id);
};
   

void client(CacheImplementor &impl) {
    std::shared_ptr<Item> sp1 = impl.FastLoadItem(1);        // Item-1
    std::shared_ptr<Item> sp2 = impl.FastLoadItem(1);        // Item-1 , accuire from the cache

    // Item-1 has 2-strong and 1-weak refrence.
    {
        std::shared_ptr<Item> sp3 = impl.FastLoadItem(2);     // Item-2
        // going to expire item2 from cache, weak_ptr for item-2 will dangle.
    }
    // Item-2 has 0-strong ref, and 1 waek ref which is expired.

    std::shared_ptr<Item> sp5 = impl.FastLoadItem(2);
    // since, Item-2 has exired, It cant find into cache. 

    std::shared_ptr<Item> sp4 = impl.FastLoadItem(3);        // Item-3
    // Item-3 has 1-strong and 1-weak refrence.
}



int main() {

    CacheImplementor implementor;
    client(implementor);

return 0;
};
