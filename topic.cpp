#include <partition.cpp>

using namespace std;

template<class Key, class Value>
class Topic {
    public:

    Topic(size_t capacity, int id) : partitions(capacity), id(id) {
    }


    vector<Partition<Key, Value>> partitions;
    int id;

};