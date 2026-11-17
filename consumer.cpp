#include <broker.cpp>
#include <topic.cpp>
#include <event.cpp>

using namespace std;
template<class Key, class Value>
class Consumer {

    unordered_map<int, vector<int>> topicIds_to_offsets;
    unordered_map<int, *Broker<Key, Value>> topicid_to_broker;
    // which broker corresponds to each partition
    Leader* controller_broker;

    

    Consumer(Leader* controller_broker) : topics(0), controller_broker(controller_broker) {
        // fetch from controller broker
        // put it in the topicid to broker
        topicid_to_broker = controller_broker->get_broker_map();
    }

    void subscribe(int topicId) {
        Broker* broker = topicid_to_broker[topicId];
        topicIds_to_offsets[topicId] = vector<int>(0, broker->numberOfPartitions(topicId));
    }
    
    vector<Event<Key, Value>> poll() {
        vector<Event<Key, Value>> result;
        for (const auto& [topicid, broker] : topicid_to_broker) {
            for (int i = 0; i < topicIds_to_offsets[topicid].size(); i++) {
                int offset = topicIds_to_offsets[topicid];
                result.push_back(broker->consume(topicid, i, offset));
            }
        }
        return result;
    }

};