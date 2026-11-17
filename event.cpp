#include <chrono>

using namespace std;

template<class Key, class Value>
class Event {
    public:

    Event(Key key, Value value) {
        this->key = key;
        this->value = value;
        this->timestamp = chrono::steady_clock::now();
    }

    Key getKey() {
        return key;
    }

    Value getValue() {
        return value;
    }

    chrono::steady_clock::time_point getTimestamp() {
        return timestamp;
    }

    private:
    Key key;
    Value value;
    chrono::steady_clock::time_point timestamp;
};

