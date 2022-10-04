# include <assert.h>
# include <iostream>

template <class t>
class myStack_abc
{
public:
    virtual void Push(const t &val) = 0;
    virtual t Pop() const = 0;
    virtual t& Top() const = 0;
    virtual bool isEmpty() = 0;
    virtual bool isFull() = 0;
};

template <class t>
class myStack
{
private:
    const int stackincreacment = 10;
    int top;
    t* stack;
    int maxSize;
    void StackOverflow();

public:
    myStack() : top(-1), maxSize(0), stack(nullptr) {}
    myStack(const int size);
    myStack(const myStack &ms);
    void Push(const t &val);
    t Pop();
    t& Top();
    bool isEmpty() {return top == -1;}
    bool isFull() {return top == maxSize - 1;}
    ~myStack() {delete[] stack;}
};

template <class t>
myStack<t>::myStack(const int size)
{
    top = -1;
    maxSize = size;
    stack = new t(maxSize);
    assert(stack != nullptr);
}

template <class t>
myStack<t>::myStack(const myStack &ms)
{
    top = ms.top;
    maxSize = ms.maxSize;
    t* newStack = new t(maxSize);
    if (newStack == nullptr)
    {
        std::cerr << "wrong" << std::endl;
    }
    for (int i = 0; i < top; ++i)
        newStack[i] = ms[i];
    delete[] stack;
    stack = newStack;
}

template <class t>
void myStack<t>::Push(const t &val)
{
    if (isFull()) StackOverflow();
    stack[++top] = val;
}

template <class t>
t myStack<t>::Pop()
{
    if (isEmpty())
    {
        std::cerr << "is empty" << std::endl;
    }
    return stack[top--];
}

template <class t>
t& myStack<t>::Top()
{
    if (isEmpty())
    {
        std::cerr << "is empty" << std::endl;
    }
    return stack[top];
}

template <class t>
void myStack<t>::StackOverflow()
{
    t* newstack = new t(maxSize + stackincreacment);
    if (newstack == nullptr)
    {
        std::cerr << "wrong" << std::endl;
    }
    for (int i = 0; i <= top; ++i)
        newstack[i] = stack[i];
    maxSize = maxSize + stackincreacment;
    delete[] stack;
    stack = newstack;
}