#include "broker.cpp"
#include "leader.cpp"
#include <thread>
#pragma once

using namespace std;
template<class Key, class Value>
class Consumer {
    public:

    unordered_map<int, vector<int>> topicIds_to_offsets;
    unordered_map<int, Broker<Key, Value>*> topicid_to_broker;
    // which broker corresponds to each partition
    Leader<Key, Value> * controller_broker;

    

    Consumer(Leader<Key, Value>* controller_broker) : topicIds_to_offsets(0), controller_broker(controller_broker) {
        // fetch from controller broker
        // put it in the topicid to broker
        topicid_to_broker = controller_broker->get_broker_map();
    }

    void subscribe(int topicId) {
        Broker<Key, Value>* broker = topicid_to_broker[topicId];
        topicIds_to_offsets[topicId] = vector<int>(broker->numberOfPartitions(topicId), 0);
    }
    
    vector<Event<Key, Value>> poll() {
        vector<Event<Key, Value>> result;
        for (const auto& [topicid, broker] : topicid_to_broker) {
            for (int i = 0; i < topicIds_to_offsets[topicid].size(); i++) {
                int offset;
                for (offset = topicIds_to_offsets[topicid][i]; offset < broker->numberOfEvents(topicid, i); offset++) {
                   result.push_back(broker->consume(topicid, i, offset));
                }
                topicIds_to_offsets[topicid][i] = offset;
            }
        }
        return result;
    }

    void* run(void* args) {
        for (int i = 0; i < 20; i++) {
            vector<Event<Key, Value>> res = poll();
            for (auto event : res) {
                event.print_event();
            }
             std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }

};