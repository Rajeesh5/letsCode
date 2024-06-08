#include "HelloWorldCmd.hpp"
#include "Server.hpp"
#include "WaitCmd.hpp"

class Client {
public:
    void run() {
        Server theServer { };
        CommandPtr waitcmd = std::make_shared<WaitCommand>(3000);
        theServer.acceptCommand(waitcmd);

        CommandPtr helloWorldOutputCommand = std::make_shared<HelloWorldOutputCommand>();
        theServer.acceptCommand(helloWorldOutputCommand);
    }
};

int main() {

    Client client {};
    client.run();
}