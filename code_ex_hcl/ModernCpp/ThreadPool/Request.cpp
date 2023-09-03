#include "Request.h"

void Request::process() 
{    
	m_callback("Starting processing request " + std::to_string(value) + "...");
} 
void Request::finish() 
{   
	m_callback("Finished request " + std::to_string(value));
}