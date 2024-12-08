#ifndef SERVICE_H
#define SERVICE_H

#include "service_if.h"

class Service {
public:
    Service();
    void send_message(const std::string& text);
    void handle_received_message(const Messenger::Message& msg);
private:
    ServiceInterface service_if_;
};

#endif // SERVICE_H