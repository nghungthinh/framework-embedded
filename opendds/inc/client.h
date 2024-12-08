#ifndef CLIENT_H
#define CLIENT_H

#include "service_if.h"

class Client {
public:
    Client();
    void send_message(const std::string& text);
    void handle_received_message(const Messenger::Message& msg);
private:
    ServiceInterface service_if_;
};

#endif // CLIENT_H