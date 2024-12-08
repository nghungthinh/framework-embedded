#include "inc/service.h"

Service::Service() {}

void Service::send_message(const std::string& text) {
    Messenger::Message message;
    message.text = text.c_str();
    message.count = 0;
    service_if_.send_message(message);
}