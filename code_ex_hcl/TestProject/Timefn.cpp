#include <iostream>
#include <ctime>
#include <atlstr.h>

int main_1(void)
{
    time_t     now;
    struct tm  ts;
    char       buf[80];

    /*
    // Get current time
    time(&now);

    // Format time, "ddd yyyy-mm-dd hh:mm:ss zzz"
    ts = *localtime(&now);
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
    std::cout << buf << "\n";
    */


    /*
    time_t seconds;

    seconds = time(NULL);
    std::cout << "Seconds since January 1, 1970 ::" << seconds << "\n";
    */
    /*
    std::time_t result = std::time(nullptr);
    std::cout << std::asctime_r(std::localtime(&result))
        << result << " seconds since the Epoch\n";
        */




        time_t rawtime;
        CString temp;
        char timeval[128];

        time(&rawtime);
        // returns current datetime as of now, once code in AD layer implemented 
        // it will return actual commit time from database.
        strftime(timeval, sizeof(timeval), "%Y-%m-%d %H:%M:%S", localtime(&rawtime));
        printf("Formatted date & time : %s\n", timeval);

    

    return 0;
}