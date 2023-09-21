#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <chrono>
#include <iostream>
#include <thread>

using namespace boost::asio;

void work_handler_1(const boost::system::error_code& ec) {
	for (int i = 0; i < 5; i++) {
		std::cout << "Msg form handler_1" << std::endl;
	}
}


void work_handler_2(const boost::system::error_code& ec) {
	for (int i = 0; i < 5; i++) {
		std::cout << "Msg form handler_2" << std::endl;
	}
}


void long_exe() {
	std::this_thread::sleep_for(std::chrono::seconds(30));
	std::cout << "End of long execution" << std::endl;
}

int main()
{
	io_service service;
	const boost::system::error_code ec;
	deadline_timer timer1(service, boost::posix_time::seconds(5));
	deadline_timer timer2(service, boost::posix_time::seconds(3));
	
	//timer1.async_wait(&work_handler_1);
	//timer1.async_wait(&work_handler_2);

	//std::thread th1{
	//	[&]() { service.run(); }
	//};
	//
	//std::thread th2{
	//	[&]() { service.run(); }
	//};

	service.post(long_exe);

	//service.run();

	std::cout << "Hi\n";
	//th1.join();
	//th2.join();

}



