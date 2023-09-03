#include <stdio.h> 
//#include <sys/resource.h> 
#include <string.h> 
#include <errno.h> 
//#include <unistd.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 

using namespace std;

#define MEM_ENV_VAR 10;   //10 MB limit.

//void setmemlimit();

int main_2(int argc, char** argv)
{
    // launch MPI here first if you are doing so

   // setmemlimit();

    // the rest of the program goes here
    // ...
    // ...

    return 0;
}


/*
void setmemlimit()
{
    struct rlimit memlimit;
    long bytes;


    bytes = MEM_ENV_VAR * 1024 * 1024;
    memlimit.rlim_cur = bytes;
    memlimit.rlim_max = bytes;
    setrlimit(RLIMIT_AS, &memlimit);
    
}
*/