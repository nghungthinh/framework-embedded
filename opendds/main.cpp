#include <iostream>
#include "main.h"
#include <thread>
#include <chrono>

void message_callback(void* ctx, const Messenger::Message& msg) {
   std::cout << "Received message: " << msg.text << " count: " << msg.count << std::endl;
}

int main(int argc, char* argv[]) {    
   std::string mode;
   for (int i = 1; i < argc; ++i) {
       if (std::string(argv[i]).substr(0, 7) == "--mode=") {
           mode = argv[i] + 7;
       }
   }
  
   ServiceInterface service_if;
  
   if (mode == "service") {
       if (!service_if.initService()) {
           std::cerr << "Failed to initialize service" << std::endl;
           return 1;
       }
      
       while (true) {
           Messenger::Message msg;
           msg.text = "Hello from service!";
           msg.count = 1;
           service_if.send_message(msg);
           std::this_thread::sleep_for(std::chrono::seconds(1));
       }
   }
   else if (mode == "client") {
       // Setup callback first
       void* context = nullptr;
       service_if.listener_ = new DataReaderListenerImpl();
       static_cast<DataReaderListenerImpl*>(service_if.listener_)->context_ = context;
       static_cast<DataReaderListenerImpl*>(service_if.listener_)->message_callback_ = message_callback;

       // Then initialize client
       if (!service_if.initClient()) {
           std::cerr << "Failed to initialize client" << std::endl;
           return 1;
       }

       while (true) {
           std::this_thread::sleep_for(std::chrono::seconds(1));
       }
   }
  
   return 0;
}