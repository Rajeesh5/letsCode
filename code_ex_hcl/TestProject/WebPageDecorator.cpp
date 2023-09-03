#include<iostream>

using namespace std;


// This interface will define the common behavoir for basic and 
// decorated webpage has.
class Webpage {
public:
	virtual void display() = 0;
};

class BasicWebpage : public Webpage {

public:
	BasicWebpage(const string& html, const string& style, const string script) :
		m_html(html), m_stylesheet(style), m_script(script) {}
	virtual void display() {
		cout << "Basic webpage with::" << endl;
		// Print the basic webpage.
	}
	virtual ~BasicWebpage() {}
private:
	std::string m_html;
	std::string m_stylesheet;
	std::string m_script;
};


class WebPageDecorator :public Webpage {       // this is also an abastrct class.

public:
	WebPageDecorator(Webpage *page):m_pWebpage(page){}
	
	virtual ~WebPageDecorator() { 
		delete m_pWebpage; 
		cout << "Deleted WebPageDecorator" << endl;
	}
	virtual void display() {
		m_pWebpage->display();
	}

protected:		// impotant to make it protected, so that it can assable from derived class.
				// decorator has only one insatance of webpage, so that it can use as aggration stack.
	Webpage* m_pWebpage;
};

class AuthorizedWebPage :public WebPageDecorator {
public:
	AuthorizedWebPage(Webpage* decoratedPage) :WebPageDecorator(decoratedPage) {}

	void authorizedUser() {
		cout << "Authorizing user" << endl;
	}
	virtual void display() {
		m_pWebpage->display();		//since protected, now we have access. 
		this->authorizedUser();
	}
	virtual ~AuthorizedWebPage() { cout << "Deteled AuthorizedWebPage" << endl; }
};


class AuthenticatedWebPage : public WebPageDecorator {
public:
	AuthenticatedWebPage(Webpage* decoratedPage) :WebPageDecorator(decoratedPage) {}
	void authenticateUser() {
		cout << "Authenticating user" << endl;
	}
	virtual void display() {
		m_pWebpage->display();		//since protected, now we have access. 
		this->authenticateUser();
	}
	virtual ~AuthenticatedWebPage() { cout << "Deleted AuthenticatedWebPage" << endl; }
};


int main_wp() {
		Webpage *myPage = new BasicWebpage("google.com","cascate","html");
		myPage = new AuthorizedWebPage(myPage);
		myPage = new AuthenticatedWebPage(myPage);
		myPage->display();

		delete myPage;
		return 0;
}








