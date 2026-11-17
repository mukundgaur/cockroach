#include <event.cpp>
#include <vector>

using namespace std; 

template<class Key, class Value>
class Partition {

    public:
    Partition(vector<Event<Key, Value>>* stream) {
        this->stream = stream;
    }

    void fetchAtIndex(int idx) {
        return stream[index];
    }

    void append(Event& event) {
        stream.push_back(event);
    }

    void append(Event&& event) {
        stream.push_back(event);
    }

    private:
    vector<Event<Key, Value>>* stream;
};