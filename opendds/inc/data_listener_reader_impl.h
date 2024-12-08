#ifndef DATA_LISTENER_READER_IMPL_H
#define DATA_LISTENER_READER_IMPL_H

#include <dds/DdsDcpsSubscriptionC.h>
#include "MessengerTypeSupportC.h"
#include "MessengerTypeSupportImpl.h"

class DataReaderListenerImpl : public virtual OpenDDS::DCPS::LocalObject<DDS::DataReaderListener> {
public:
    void *context_;
    void (*message_callback_)(void *, const Messenger::Message&);
    
    DataReaderListenerImpl() : context_(nullptr), message_callback_(nullptr) {}
    
    virtual void on_data_available(DDS::DataReader_ptr reader);
    virtual void on_requested_deadline_missed(DDS::DataReader_ptr, const DDS::RequestedDeadlineMissedStatus&) {}
    virtual void on_requested_incompatible_qos(DDS::DataReader_ptr, const DDS::RequestedIncompatibleQosStatus&) {}
    virtual void on_sample_rejected(DDS::DataReader_ptr, const DDS::SampleRejectedStatus&) {}
    virtual void on_liveliness_changed(DDS::DataReader_ptr, const DDS::LivelinessChangedStatus&) {}
    virtual void on_subscription_matched(DDS::DataReader_ptr, const DDS::SubscriptionMatchedStatus&) {}
    virtual void on_sample_lost(DDS::DataReader_ptr, const DDS::SampleLostStatus&) {}
};

#endif // DATA_LISTENER_READER_IMPL_H