#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

void work_for_io_service(const boost::system::error_code& /*e*/)
{
  std::cout << "Non-blocking wait() \n";
}

void task(int task_id, std::string msg) 
{
  std::cout << "Task ID :: " << task_id << " message = " << msg << std::endl;
}

class Task {

public:
  void operator() (std::string& msg) {
    std::cout << "Inside class ::" << msg; 
  }
};



int main()
{
  boost::asio::io_service io;

  boost::asio::deadline_timer timer1(io, boost::posix_time::seconds(5));
  boost::asio::deadline_timer timer2(io, boost::posix_time::seconds(10));

  // work_for_io_service() will be called 
  // when async operation (async_wait()) finishes  
  // note: Though the async_wait() immediately returns
  //       but the callback function will be called when time expires
  timer1.async_wait(&work_for_io_service);
  timer2.async_wait(&work_for_io_service);
  
  std::cout << " If we see this before the callback function, we know async_wait() returns immediately.\n \
                 This confirms async_wait() is non-blocking call!\n";

  // Binding parameter value to callback

  boost::asio::deadline_timer timer3(io,boost::posix_time::seconds(2));
  timer3.async_wait(boost::bind(task, 123, "Test msg"));

  // How to bind class member function ??
  // boost::asio::deadline_timer timer4(io,boost::posix_time::seconds(1));
  // timer4.async_wait(boost::bind(&Task; ::Task(), this "Test msg"));

  // the callback function, work_for_io_service(), will be called 
  // from the thread where io.run() is running. 
  // Remember that the io_service::run() function will returns when there 
  // is no more "work" to do.


  io.run();

  return 0;
}