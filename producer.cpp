#include "broker.cpp"
#include "leader.cpp"
#include <unordered_map>
#include <thread>
#pragma once

using namespace std;

template<class Key, class Value>
class Producer {
    public:

    unordered_map<int, Broker<Key, Value>*> topicid_to_broker;
    // which broker corresponds to each partition
    Leader<Key, Value>* controller_broker;


    Producer(Leader<Key, Value>* controller_broker) : controller_broker(controller_broker) {
        // fetch from controller broker
        // put it in the topicid to broker
        topicid_to_broker = controller_broker->get_broker_map();
    }

    void produce(int topicId, Event<Key, Value> event) {
        Broker<Key, Value>* broker = topicid_to_broker[topicId];
        size_t pos = std::hash<Key>{}(event.getKey());
        broker->addEvent(event, topicId, pos % broker->numberOfPartitions(topicId));
    }

    void* run(void* args) {
        for (int i = 0; i < 10; i++) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            this->produce(0, Event<Key, Value>{i, i * 10});
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }

};