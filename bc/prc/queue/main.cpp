#include <iostream>
#include <cstring>

using namespace std;

typedef signed int Data;

class Queue{
  unsigned int capacity; //kapacita fronty
  unsigned int counter; //pocitadlo prvku
  Data *data;
  unsigned int f, b; //indexy čela a konce fronty
public:
  Queue(unsigned int size);
  Queue(Queue &other);
  ~Queue();
  unsigned int getCapacity() const;
  void pushBack(Data d);
  Data front() const;
  void popFront();
  bool empty() const;
  bool full();
};



using namespace std;

Queue::Queue(unsigned int size)
    :capacity(size), data(new Data[capacity]),f(0),b(0),counter(0)

{
    memset(data, 0, capacity*sizeof(Data));
}

Queue::Queue(Queue &other)
    : capacity(other.capacity), data(new Data[capacity]), f(other.f), b(other.b), counter(other.counter)
{
    memcpy(this->data, other.data, capacity*sizeof (Data));
}

Queue::~Queue(){
    delete [] data;
}

unsigned int Queue::getCapacity() const{
    return capacity;
}

void Queue::pushBack(Data d)
{
    if(full()){
        cout << "full" << endl;
    }
    else
    {
        if(b == capacity){
                b = 0;
        }
        data[b] = d;
        b++;
        counter++;
    }
}

 Data Queue::front() const{
    return data[f];
}


void Queue::popFront(){
    if(empty()){
        std::cout << "empty" << std::endl;
    }
    else
    {
        f++;
        if(f == capacity){
                f = 0;
        }
        counter--;
    }
}

bool Queue::empty() const{
    return (counter == 0);
}

bool Queue::full(){
    return (counter == capacity);
}



int main()
{
    Queue q(5);
    q.getCapacity();
    q.empty();
    q.popFront();
    q.pushBack(1);
   // q.popFront();
    //q.popFront();
    q.front();
    q.empty();
    q.pushBack(2);
    q.pushBack(3);
    q.front();
    q.full();
    q.pushBack(4);
    //q.popFront();
    q.front();
    q.pushBack(5);
    q.pushBack(6);
    q.popFront();
    q.pushBack(6);
    q.pushBack(7);

    return 0;
}
