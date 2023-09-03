#pragma once 
#ifndef REQUEST_H 
#define REQUEST_H
#include "abstract_request.h"
#include <string>
#include <functional>
using namespace std;


// typedef void (*DoCallBack)(string text);
// typedef std::function<void(string)> DoCallBack;
 
using DoCallBack = std::function<void(string)>;

class Request : public AbstractRequest 
{ 

public:    
	int  getValue() { return value; }
	void setValue(int value) { this->value = value; }    
	void setOutput(DoCallBack fnc) { m_callback = fnc; }
	void process();    
	void finish(); 

private:
	int value;
	DoCallBack m_callback;
}; 
#endif