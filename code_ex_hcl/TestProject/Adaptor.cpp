#include<iostream>


class Object {};
class Json {};


class WebRequester {
public:
	virtual int request(Object*) = 0;
};

class WebService {
public:
	WebService(std::string url):m_url(url){}
	Json* request(Json*){}
private:
	std::string m_url;
};


class WebAdapter : public WebRequester {

public:
	void connect(WebService* currentService) {
		m_pService = currentService;
		/* Connect to the web service */
	}

	int request(Object *request) {
		Json* result = this->toJson(request);
		Json* response = m_pService->request(result);
		if (response != nullptr)
			return 200; // OK status code
		return 500; // Server error status code
	}
private:
	WebService* m_pService;
	Json* toJson(Object* input) { }
};



class WebClient {

public:
	WebClient(WebRequester* webRequester) {
		this->webRequester = webRequester;
	}
	void doWork() {
		Object* object = makeObject();
		int status = webRequester->request(object);
		if (status == 200) {
			std::cout << "OK\n";
		}
		else {
			std::cout << "Not OK\n";
		}
		return;
	}
private:
	Object* makeObject() { return new Object(); } // Make an Object
	WebRequester* webRequester;
};


int main() {
	WebService *service = new WebService("Host: https://google.com\n\r");
	WebAdapter *adapter = new WebAdapter();
	adapter->connect(service);
	WebClient *client = new WebClient(adapter);
	client->doWork();	
	return 0;
}


