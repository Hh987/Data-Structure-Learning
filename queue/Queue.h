# include <assert.h>
# include <iostream>

//ABC
template <class t>
class Queue
{
public:
    Queue() {}
    ~Queue() {}
    virtual bool EnQueue(const t &val) = 0;
    virtual bool DeQueue(t &x) = 0;
    virtual bool isEmpty() = 0;
    virtual bool isFull() = 0;
    virtual void MakeEmpty() = 0;
    virtual bool getFront(t &x) = 0;
    virtual int getSize() const = 0;
};

// //循环链表有空节点判满
// template <class t>
// class SeqQueue : Queue<t>
// {
// private:
//     t* data;
//     int front, rear;
//     int maxsize;

// public:
//     SeqQueue(int sz = 10);
//     ~SeqQueue() {delete[] data;}
//     bool EnQueue(const t &val);
//     bool DeQueue(t &x);
//     bool isEmpty() {return rear == front;}
//     bool isFull() {return (rear + 1) % maxsize == front;}
//     void MakeEmpty() {rear = front = 0;}
//     bool getFront(t &x);
//     int getSize() const {return (rear - front + maxsize) % maxsize;}
//     friend std::ostream& operator<< (std::ostream &os, SeqQueue<int>& q);
// };


// template <class t>
// SeqQueue<t>::SeqQueue(int sz) : front(0), rear(0), maxsize(sz)
// {
//     data = new t[maxsize];
//     assert(data != nullptr);
// }

// template <class t>
// bool SeqQueue<t>::EnQueue(const t &val)
// {
//     if (isFull()) return false;
//     data[rear] = val;
//     rear = (rear + 1) % maxsize;
//     return true;
// }

// template <class t>
// bool SeqQueue<t>::DeQueue(t &x)
// {
//     if (isEmpty()) return false;
//     x = data[front];
//     front = (front + 1) % maxsize;
//     return true;
// }

// template <class t>
// bool SeqQueue<t>::getFront(t &x)
// {
//     if (isEmpty()) return false;
//     x = data[front];
//     return true;
// }

// std::ostream& operator<< (std::ostream &os, SeqQueue<int>& q)
// {
//     os << "front = " << q.front << ", rear = " << q.rear << std::endl;
//     for (int i = q.front; i != q.rear; i = (i + 1) % q.maxsize)
//     {
//         os << q.data[i] << ' ';
//     }
//     os << std::endl;
//     return os;
// }

//循环链表无空节点判满
template <class t>
class SeqQueue : Queue<t>
{
private:
    t* data;
    int front, rear;
    int maxsize;
    int tag;
    void QueueExpansion();
    void QueueReduction();

public:
    SeqQueue(int sz = 10);
    ~SeqQueue() {delete[] data;}
    bool EnQueue(const t &val);
    bool DeQueue(t &x);
    bool isEmpty() {return rear == front;}
    bool isFull() {return (rear + 1) % maxsize == front;}
    void MakeEmpty() {rear = front = 0;}
    bool getFront(t &x);
    int getSize() const {return (rear - front + maxsize) % maxsize;}
    friend std::ostream& operator<< (std::ostream &os, SeqQueue<int>& q);
};

template <class t>
SeqQueue<t>::SeqQueue(int sz) : front(0), rear(0), maxsize(sz), tag(0)
{
    data = new t[maxsize];
    assert(data != nullptr);
}

//无扩充和减少
// template <class t>
// bool SeqQueue<t>::EnQueue(const t &val)
// {
//     if (isFull()) return fales;
//     tag = 1;
//     data[rear] = val;
//     rear = (rear + 1) % maxsize;
//     return true;
// }

// template <class t>
// bool SeqQueue<t>::DeQueue(t &x)
// {
//     if (isEmpty()) return false;
//     tag = 0;
//     x = data[front];
//     front = (front + 1) % maxsize;
//     return true;
// }

template <class t>
bool SeqQueue<t>::getFront(t &x)
{
    if (isEmpty()) return false;
    x = data[front];
    return true;
}

std::ostream& operator<< (std::ostream &os, SeqQueue<int>& q)
{
    os << "front = " << q.front << ", rear = " << q.rear << std::endl;
    for (int i = q.front; i != q.rear; i = (i + 1) % q.maxsize)
    {
        os << q.data[i] << ' ';
    }
    os << std::endl;
    return os;
}

template <class t>
void SeqQueue<t>::QueueExpansion()
{
    int newsize = maxsize * 2;
    t* newqueue = new t(newsize);
    for (int i = front; i != rear; i = (i + 1) % maxsize)
    {
        newqueue[i] = data[i];
    }
    delete[] data;
    data = newqueue;
    maxsize = newsize;
}

template <class t>
void SeqQueue<t>::QueueReduction()
{
    int newsize = (int)(maxsize * 0.5);
    t* newqueue = new t(newsize);
    int j = 0;
    for (int i = front; i != rear; i = (i + 1) % maxsize)
    {
        newqueue[j++] = data[i];
    }
    front = 0;
    rear = j;
    delete[] data;
    data = newqueue;
    maxsize = newsize;
}

template <class t>
bool SeqQueue<t>::EnQueue(const t &val)
{
    if (isFull()) QueueExpansion();
    tag = 1;
    data[rear] = val;
    rear = (rear + 1) % maxsize;
    return true;
}

template <class t>
bool SeqQueue<t>::DeQueue(t &x)
{
    if (isEmpty()) return false;
    if (getSize() < maxsize * 0.25) QueueReduction();
    tag = 0;
    x = data[front];
    front = (front + 1) % maxsize;
    return true;
}