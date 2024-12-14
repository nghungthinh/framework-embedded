#ifndef OPENDDS_IF_H
#define OPENDDS_IF_H

#include "DataReaderListenerImpl.h"
#include "Boilerplate.h"
#include <dds/DCPS/Service_Participant.h>
#include <model/Sync.h>
#include <stdexcept>
#include <iostream>

using namespace examples::boilerplate;

class DDSHandler {
private:
    // Message Topic
    DDS::DomainParticipantFactory_var dpf_;
    DDS::DomainParticipant_var participant_;
    DDS::Topic_var topic_;
    DDS::Subscriber_var subscriber_;
    DDS::Publisher_var publisher_;
    DDS::DataWriter_var writer_;
    DDS::DataReader_var reader_;
    Messenger::MessageDataWriter_var message_writer_;

    DataReaderListenerImpl* listener_impl_;
public:
    DDSHandler();
    ~DDSHandler();
};

#endif // OPENDDS_IF_H
