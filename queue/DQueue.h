# include <assert.h> 
# include <iostream>

template <class t>
class DQueue
{
public:
    // virtual bool getHead(t &x) = 0;
    // virtual bool getTail(t &x) = 0;
    virtual bool isEmpty() = 0;
    virtual bool isFull() = 0;
    virtual bool EnQueueHead(const t &x) = 0;
    virtual bool EnQueueTail(const t &x) = 0;
    virtual bool DeQueueHead(t &x) = 0;
    virtual bool DeQueueTail(t &x) = 0;
};

template <class t>
class SeqDQueue : public DQueue<t>
{
private:
    int end1, end2;
    int maxsize;
    t* data;

public:
    SeqDQueue(int sz = 10);
    ~SeqDQueue() {delete[] data;}
    bool isEmpty();
    bool isFull();
    bool EnQueueHead(const t &x);//end2
    bool EnQueueTail(const t &x);//end1
    bool DeQueueHead(t &x);//end1
    bool DeQueueTail(t &x);//end2
    friend std::ostream& operator<< (std::ostream &os, SeqDQueue<int>& q);

};

template <class t>
bool SeqDQueue<t>::isEmpty()
{
    if (end1 == maxsize - 1) return end2 == 0;
    else return end1 == end2 - 1;
}

template <class t>
bool SeqDQueue<t>::isFull()
{
    return (end2 + 1) % maxsize == end1;
}

template <class t>
SeqDQueue<t>::SeqDQueue(int sz) : end1(0), end2(1), maxsize(sz)
{
    data = new t(maxsize);
    assert(!(data == nullptr));
}

template <class t>
bool SeqDQueue<t>::EnQueueHead(const t &x)
{
    if (isFull()) return false;
    data[end1] = x;
    if (end1 == 0) end1 = maxsize - 1;
    else end1 = (end1 - 1) % maxsize;
    return true;
}

template <class t>
bool SeqDQueue<t>::EnQueueTail(const t &x)
{
    if (isFull()) return false;
    data[end2] = x;
    end2 = (end2 + 1) % maxsize;
    return true;
}

template <class t>
bool SeqDQueue<t>::DeQueueHead(t &x)
{
    if (isEmpty()) return false;
    end1 = (end1 + 1) % maxsize;
    x = data[end1];
    return true;
}

template <class t>
bool SeqDQueue<t>::DeQueueTail(t &x)
{
    if (isEmpty()) return false;
    if (end2 == 0) end2 = maxsize - 1;
    else end2 = (end2 - 1) % maxsize;
    x = data[end2];
    return true;
}

std::ostream& operator<< (std::ostream &os, SeqDQueue<int>& q)
{
    os << "end1 = " << q.end1 << ", end2 = " << q.end2 << std::endl;
    for (int i = q.end1; i != q.end2; i = (i + 1) % q.maxsize)
    {
        os << q.data[i] << ' ';
    }
    os << std::endl;
    return os;
}