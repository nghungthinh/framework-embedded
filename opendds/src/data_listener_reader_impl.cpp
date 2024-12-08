#include "inc/data_listener_reader_impl.h"

void DataReaderListenerImpl::on_data_available(DDS::DataReader_ptr reader) {
    Messenger::MessageDataReader_var reader_i = 
        Messenger::MessageDataReader::_narrow(reader);

    Messenger::Message message;
    DDS::SampleInfo info;
    
    while (reader_i->take_next_sample(message, info) == DDS::RETCODE_OK) {
        if (info.valid_data && message_callback_) {
            std::cout << "Received message: " << message.text << " count: " << message.count << std::endl;
            message_callback_(context_, message);
        }
    }
}