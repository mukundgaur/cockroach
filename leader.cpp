#include <topic.cpp>
#include <partition.cpp>
#include <broker.cpp>
#include <thread>

using namespace std;
template<class Key, class Value>
class Leader {

    Leader() {
        for (int i = 0; i < 10; i++) {
            topicid_to_topic[i] = new Topic(2, i);
            unordered_map<int, Topic<Key, Value>*>* currmap = new unordered_map<int, Topic<Key, Value>*>();
            currmap[i] = topicid_to_topic[i];
            topicid_to_broker[i] = new Broker(currmap);
        }
    }

    unordered_map<int, *Broker<Key, Value>> get_broker_map() {
        return topicid_to_broker;
    }

    private:
    ordered_map<int, *Topic<Key, Value>> topicid_to_topic;
    unordered_map<int, *Broker<Key, Value>*> topicid_to_broker;

    // all the topics
    // all the partitions
    // which broker is the leader for each partition
    // which brokers are the followers for each partition



};