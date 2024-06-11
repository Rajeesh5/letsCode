#include <iostream>
#include <memory>

class Handler {
public:
    virtual ~Handler() = default;
    void setNext(std::shared_ptr<Handler> nextHandler) {
        next = nextHandler;
    }
    virtual void handleRequest(int request);
protected:
    virtual bool canHandle(int request) = 0;
private:
    std::shared_ptr<Handler> next;
};

void Handler::handleRequest(int request) {
    if (next) {
        next->handleRequest(request);
    } else {
        std::cout << "No handler available for request " << request << std::endl;
    }
 }

class ConcreteHandler1 : public Handler {
protected:
    bool canHandle(int request) override {
        return request <= 10;
    }
public:
    void handleRequest(int request) override {
        if (canHandle(request)) {
            std::cout << "Handler 1 handling request " << request << std::endl;
        } else {
            Handler::handleRequest(request);
        }
    }
};

class ConcreteHandler2 : public Handler {
protected:
    bool canHandle(int request) override {
        return request > 10 && request <= 20;
    }
public:
    void handleRequest(int request) override {
        if (canHandle(request)) {
            std::cout << "Handler 2 handling request " << request << std::endl;
        } else {
            Handler::handleRequest(request);
        }
    }
};

int main() {
    std::shared_ptr<Handler> handler1 = std::make_shared<ConcreteHandler1>();
    std::shared_ptr<Handler> handler2 = std::make_shared<ConcreteHandler2>();

    handler1->setNext(handler2);

    handler1->handleRequest(5);   // Handled by ConcreteHandler1
    handler1->handleRequest(15);  // Handled by ConcreteHandler2
    handler1->handleRequest(25);  // Not handled

    return 0;
}
