#ifndef SERVICE_IF_H
#define SERVICE_IF_H

#include <dds/DdsDcpsInfrastructureC.h>
#include <dds/DdsDcpsPublicationC.h>
#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/WaitSet.h>
#include "MessengerTypeSupportImpl.h"
#include "data_listener_reader_impl.h"

class ServiceInterface {
private:
    DDS::DomainParticipant_var participant_;
    DDS::Topic_var topic_;
    DDS::Publisher_var publisher_;
    DDS::Subscriber_var subscriber_;
    DDS::DataWriter_var writer_;
    Messenger::MessageDataWriter_var message_writer_;

public:
    DataReaderListenerImpl* listener_;
    ServiceInterface();
    ~ServiceInterface();
    bool initService();    // For service side
    bool initClient();     // For client side
    void send_message(const Messenger::Message& message);

private:
    bool initParticipant();
    bool registerTopic();
    bool createMessagerTopicWriter(bool isBlock);
    bool createMessagerTopicReader();
};

#endif