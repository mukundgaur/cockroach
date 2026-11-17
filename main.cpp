#include "leader.cpp"
#include "consumer.cpp"
#include "producer.cpp"
#include <thread>

using namespace std;

int main() {
    Leader<int, int>* leader = new Leader<int, int>();
    Consumer<int, int>* consumer1 = new Consumer<int, int>(leader);
    Producer<int, int>* producer1 = new Producer<int, int>(leader);
    consumer1->subscribe(0);

    thread t1(&Consumer<int, int>::run, consumer1, nullptr);
    thread t2(&Producer<int, int>::run, producer1, nullptr);

    t1.join();
    t2.join();


    return 0;
}