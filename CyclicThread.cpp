#include <iostream>
#include <thread>
#include <functional>
#include <chrono>
#include <vector>
#include <atomic>                                       // For using std::atomic<bool>

using namespace std;


std::atomic<bool> stopFlag(false);                      // Atomic flag to control the periodic task

using CallBack = std::function<void(unsigned int, vector<std::string>& )>;
vector<std::string> TimeBuffer;

void GetTimeStamp(unsigned int interval_ms, vector<std::string> &buffer) {
    
    while (!stopFlag.load(std::memory_order_relaxed)) {

        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        // Convert the time_point to a time_t (if needed)
        std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
        // return the current time
        // std::cout << "Current time: " << std::ctime(&now_time_t) ;

        buffer.push_back(std::ctime(&now_time_t));

        std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms)); 
        //return ("Current time: " + string(std::ctime(&now_time_t)) );
    }
}

void PrintBuffer(vector<std::string> &buffer) {
    for(auto item:buffer) {
        std::cout << item ;
    }
}

class CyclicThread 
{
    public: 
    CyclicThread(const CyclicThread&) = delete; 
    CyclicThread& operator=(const CyclicThread&) = delete; 
    CyclicThread(CallBack &call_back, unsigned int ms):
        m_pThread(nullptr),m_callBack(call_back),
        m_timeIntervalMS(ms),m_isReady(true) {}

    void StartThread() {
        if(m_isReady) {
            m_pThread = new thread(m_callBack,m_timeIntervalMS,std::ref(TimeBuffer));
            m_isRunning = true;
        }
    }
    
    void StopThread() {
        if(m_isRunning) {                                                                
            stopFlag.store(true, std::memory_order_relaxed);    // Set the stop flag to true to stop the periodic task       
            m_isRunning = false;                                // Now thread is not running
        }

        // Now need to call distructor manually to join the thread; 
        // So that next time we can re-launch the same thread.       
        
        if(m_pThread && m_pThread->joinable()) {
            m_pThread->join();
            delete m_pThread; 
            m_pThread = nullptr;
            stopFlag = false;       // flag required for looping. 
        }       
        
    }

    ~CyclicThread() {
        StopThread();
        m_isReady = false;

    } 

    // Need to check warpper moving behavoiur
    // CyclicThread(CyclicThread && obj); 
    // CyclicThread & operator=(CyclicThread && obj); 

private:

    bool m_isReady = false;         // true, means all required parameter intialised 
    bool m_isRunning = false;       // true, means now thread is running 
    unsigned int m_timeIntervalMS;  // In millisecond
    thread *m_pThread;
    CallBack m_callBack; 

};

int main()
{
    CallBack obj = GetTimeStamp;
    CyclicThread cthraed(obj,1000);

    cout << "First Reading " << std::endl;
    cthraed.StartThread();
    std::this_thread::sleep_for(std::chrono::seconds(10)); 
    cthraed.StopThread();    
    
    cout << "Second Reading " << std::endl;
    cthraed.StartThread();
    std::this_thread::sleep_for(std::chrono::seconds(5)); 
    cthraed.StopThread();

    PrintBuffer(TimeBuffer);

    return 0;
}