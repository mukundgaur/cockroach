#include <vector>
#include <unordered_map>
#include "topic.cpp"
#pragma once
using namespace std;
template<class Key, class Value>
class Broker {

    public:

    Broker(unordered_map<int, Topic<Key, Value>*>* id_to_topic) : id_to_topic(id_to_topic) {

    }
    

    void addEvent(Event<Key, Value>& event, int topicId, int partitionId) {
        (*id_to_topic)[topicId]->partitions[partitionId].append(event);
    }

    void addEvent(Event<Key, Value>&& event, int topicId, int partitionId) {
        (*id_to_topic)[topicId]->partitions[partitionId].append(event);
    }

    Event<Key, Value> consume(int topicId, int partitionId, int offset) {
        return (*id_to_topic)[topicId]->partitions[partitionId].fetchAtIndex(offset);
    }

    int numberOfPartitions(int topicId) {
        return((*id_to_topic)[topicId])->partitions.size();
    }

    int numberOfEvents(int topicId, int partitionId) {
        return (*id_to_topic)[topicId]->partitions[partitionId].size();
    }


    void run() {
        // if there is something in the work queue, add it
        // otherwise just keep spinning
    }


    private:
    // topics its responsible for
    unordered_map<int, Topic<Key, Value>*>* id_to_topic;
    
};