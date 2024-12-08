#include "inc/service_if.h"
#include <dds/DCPS/Service_Participant.h>

ServiceInterface::ServiceInterface() : listener_(nullptr) {
}

ServiceInterface::~ServiceInterface() {
    if (!CORBA::is_nil(participant_.in())) {
        participant_->delete_contained_entities();
        DDS::DomainParticipantFactory_var dpf = TheParticipantFactory;
        dpf->delete_participant(participant_);
    }
    delete listener_;
}

bool ServiceInterface::initParticipant() {
    const char* args[] = {
        "-DCPSConfigFile",
        "/Users/nghungthinh/Desktop/framework-embedded/opendds/rtps.ini"
    };
    int argc_new = sizeof(args) / sizeof(args[0]);
    DDS::DomainParticipantFactory_var dpf = 
        TheParticipantFactoryWithArgs(argc_new, const_cast<char**>(args));
    
    participant_ = dpf->create_participant( 42, 
                                            PARTICIPANT_QOS_DEFAULT, 
                                            0, 
                                            OpenDDS::DCPS::DEFAULT_STATUS_MASK);
        
    return !CORBA::is_nil(participant_.in());
}

bool ServiceInterface::registerTopic() {
    Messenger::MessageTypeSupport_var ts = new Messenger::MessageTypeSupportImpl;
    if (ts->register_type(participant_.in(), "") != DDS::RETCODE_OK) {
        return false;
    }
    
    topic_ = participant_->create_topic("Message Topic",
                                        ts->get_type_name(),
                                        TOPIC_QOS_DEFAULT,
                                        0,
                                        OpenDDS::DCPS::DEFAULT_STATUS_MASK);
        
    return !CORBA::is_nil(topic_.in());
}

bool ServiceInterface::createMessagerTopicWriter(bool isBlock) {
    publisher_ = participant_->create_publisher(
        PUBLISHER_QOS_DEFAULT, nullptr, 
        OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    
    if (CORBA::is_nil(publisher_.in())) return false;
    
    DDS::DataWriterQos writer_qos;
    publisher_->get_default_datawriter_qos(writer_qos);
    writer_qos.reliability.kind = isBlock ? 
        DDS::RELIABLE_RELIABILITY_QOS : 
        DDS::BEST_EFFORT_RELIABILITY_QOS;
    
    writer_ = publisher_->create_datawriter(
        topic_.in(), writer_qos, nullptr,
        OpenDDS::DCPS::DEFAULT_STATUS_MASK);
        
    if (CORBA::is_nil(writer_.in())) return false;
    
    message_writer_ = Messenger::MessageDataWriter::_narrow(writer_.in());
    return !CORBA::is_nil(message_writer_.in());
}


bool ServiceInterface::createMessagerTopicReader() {
    subscriber_ = participant_->create_subscriber(
        SUBSCRIBER_QOS_DEFAULT, nullptr,
        OpenDDS::DCPS::DEFAULT_STATUS_MASK);
        
    if (CORBA::is_nil(subscriber_.in())) return false;
    
    DDS::DataReaderQos reader_qos;
    subscriber_->get_default_datareader_qos(reader_qos);
    reader_qos.reliability.kind = DDS::RELIABLE_RELIABILITY_QOS;
    
    if (!listener_) return false;
    
    DDS::DataReader_var reader = subscriber_->create_datareader(
        topic_.in(), reader_qos, listener_,
        OpenDDS::DCPS::DEFAULT_STATUS_MASK);
        
    return !CORBA::is_nil(reader.in());
}

bool ServiceInterface::initService() {
   std::cout << "Starting initService" << std::endl;
   
   bool particInit = initParticipant();
   std::cout << "Participant init: " << particInit << std::endl;
   
   bool topicInit = registerTopic();
   std::cout << "Topic init: " << topicInit << std::endl;
   
   bool writerInit = createMessagerTopicWriter(true);
   std::cout << "Writer init: " << writerInit << std::endl;

   return particInit && topicInit && writerInit;
}

bool ServiceInterface::initClient() {
    std::cout << "Starting initService" << std::endl;
   
    bool particInit = initParticipant();
    std::cout << "Participant init: " << particInit << std::endl;
    
    bool topicInit = registerTopic();
    std::cout << "Topic init: " << topicInit << std::endl;

    if (!createMessagerTopicReader()) {
        std::cerr << "Reader creation failed" << std::endl;
        return false;
    }
    return particInit && topicInit;
}

void ServiceInterface::send_message(const Messenger::Message& message) {
    DDS::ReturnCode_t error = message_writer_->write(message, DDS::HANDLE_NIL);
    if (error != DDS::RETCODE_OK) {
        std::cerr << "Error writing message: " << error << std::endl;
    }
}