#include "event.cpp"
#include <vector>
#pragma once

using namespace std; 

template<class Key, class Value>
class Partition {

    public:
    Partition() {
        this->stream = new vector<Event<Key, Value>>();
    }

    Event<Key, Value> fetchAtIndex(int idx) {
        return stream->at(idx);
    }

    int size() {
        return (int) (this->stream->size());
    }

    void append(Event<Key, Value>& event) {
        stream->push_back(event);
    }

    void append(Event<Key, Value>&& event) {
        stream->push_back(event);
    }

    private:
    vector<Event<Key, Value>>* stream;
};