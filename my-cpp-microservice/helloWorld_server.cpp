#include <iostream>
#include <string>
#include <pistache/endpoint.h>

using namespace Pistache;

class HelloWorldHandler : public Http::Handler {
public:
    HTTP_PROTOTYPE(HelloWorldHandler)

    void onRequest(const Http::Request& request, Http::ResponseWriter response) override {
        std::string message = "Hello, World!";
        response.send(Http::Code::Ok, message);
    }
};

int main() {
    Address addr(Ipv4::any(), Port(8080));

    auto opts = Http::Endpoint::options().threads(1);
    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(Http::make_handler<HelloWorldHandler>());
    server.serve();
}