#pragma once

# include <iostream>
// //线性表抽象基类
// template <class Type>
// class LinearList
// {
//     public:
//         LinearList();
//         ~LinearList();
//         virtual int size() const = 0;
//         virtual int length() const = 0;
//         virtual int search(Type &x) const = 0;
//         virtual int locate(int i) const = 0;
//         virtual void setData(int i, const Type &x) = 0;
//         virtual bool getData(int i, Type &x) const = 0;
//         virtual bool insert(int i, const Type &x) = 0;
//         virtual bool remove(int i, Type &x) = 0;
//         virtual bool isFull() = 0;
//         virtual bool isEmpty() = 0;
//         virtual void input() = 0;
//         virtual void output() = 0;
// };

//动态线性表
// const int defautSize = 5;
// template <typename Type>
// class SeqList
// {
//     protected:
//         Type* data;
//         int maxSize;
//         int last;
//         void reSize(int newSize);
//     public:
//         SeqList(int sz = defautSize);
//         SeqList(SeqList<Type> &S);
//         ~SeqList() {delete[] data;}
//         SeqList<Type>& operator=(SeqList<Type> &L);
//         int size() const {return maxSize;}
//         int length() const {return last + 1;}
//         int search(Type &x) const ;
//         int locate(int i) const;
//         void setData(int i, const Type &x);
//         bool getData(int i, Type &x) const;
//         bool insert(int i, const Type &x);
//         bool remove(int i, Type &x);
//         bool isFull() {return last == maxSize - 1;}
//         bool isEmpty() {return last == -1;}
//         void input();
//         void output();
// };

template <class type> class List;
template <class type>
class ListNode
{
    friend class List<type>;
public:
    type data;
    ListNode<type>* link;

public:
    ListNode() {link = nullptr;}
    ListNode(type &item) : data(item), link(nullptr) {}
    ListNode<type>* GetNext() {return link;}            //获取下一表元
    void SetData(const type &val) {data = val;}
    // ListNode<type>* operator->() {return link;}
    

};

template <class type>
class List
{
private:
    ListNode<type>* first, current, last;

public:
    List() {first = new ListNode<type>;}
    List(const type &value) {first = new ListNode<type>(value);}
    List(const List<type> &L);
    ~List();

public:
    ListNode<type>* GetHead() const {return first;}
    void SetHead(ListNode<type>* head) {first = head;}
    int Length();
    ListNode<type>* Locate(int i) const;
    ListNode<type>* Search(const type &val) const;
    void SetData(int i, const type &val);
    bool remove(int i);
    bool insert(int i, const type &val);
    void MakeEmpty();
    bool isEmpty() {return first == last;}
    void input(type endTag);
    void output();
    List<type> operator=(List<type> &L);

};

template <class type>
List<type>::~List()
{
    MakeEmpty();
    delete first;
}

template <class type>
int List<type>::Length()
{
    int count = 0;
    ListNode<type>* p = first -> link;
    while (p != nullptr)
    {
        p = p -> link;
        ++count;
    }
    return count;
}

template <class type>
ListNode<type>* List<type>::Locate(int i) const
{
    if (i < 0)
        return nullptr;
    int n = 0;
    ListNode<type>* p = first;
    while (n < i && p != nullptr)
    {
        p = p -> link;
        ++n;
    }
    return p;
}

template <class type>
ListNode<type>* List<type>::Search(const type &val) const
{
    ListNode<type>* p = first -> link;
    while (p != nullptr)
    {
        if (p -> data == val)
            return p;
        p = p-> link;
    }
    return p;
}

template<class type>
void List<type>::SetData(int i, const type &val)
{
    ListNode<type>* p = Locate(i);
    p -> data = val;
}

template <class type>
bool List<type>::remove(int i)
{
    if (i <= 0) return false;
    ListNode<type>* p = Locate(i - 1), q;
    q = p -> link;
    if (p == nullptr || q == nullptr) return false;
    p -> link = q -> link;
    if (q == last) last = p;
    delete q;
    return true;
}

template <class type>
bool List<type>::insert(int i, const type &val)
{
    if (i <= 0 || i > this -> Length()) return false;
    ListNode<type>* p = Locate(i - 1);
    if (p == nullptr) return false;
    ListNode<type>* q = new ListNode<type>(val);
    q -> link = p -> link;
    p -> link = q;
    if (q -> link == nullptr) last = q;
    return true;
}

template <class type>
void List<type>::MakeEmpty()
{
    ListNode<type>* q;
    while (first -> link != nullptr)
    {
        q = first -> link;
        first -> link = q -> link;
        delete q;
    }
}

template <class type>
void List<type>::input(type endTag)
{
    ListNode<type>* newListNode, *last;
    type val;
    MakeEmpty();
    std::cin >> val;
    last = first;
    while (val != endTag)
    {
        newListNode = new ListNode<type>(val);
        if (newListNode == nullptr)
        {
            std::cerr << "wrong" << std::endl;
            std::exit(1);
        }
        last -> link = newListNode;
        last = newListNode;
        std::cin >> val;
    }
}

template <class type>
void List<type>::output()
{
    ListNode<type>* current = first -> link;
    while (current != nullptr)
    {
        std::cout << current -> data << ' ';
        current = current -> link;
    }
    std::cout << '\n';
}

template <class type>
List<type> List<type>::operator=(List<type> &L)
{
    type value;
    ListNode<type>* srcptr = L.GetHead();
    ListNode<type>* destptr = first = new ListNode<type>;
    while (srcptr -> link != nullptr)
    {
        value = srcptr -> link -> data;
        destptr -> link = new ListNode<type>(value);
        destptr = destptr -> link;
        srcptr = srcptr -> link;
    }
    destptr -> link = nullptr;
    return *this;
}

template <class type> class DblList;
template <class type> 
class DblListNode
{
    friend class DblList<type>;
private:
    type data;
    DblListNode<type>* rlink, llink;

public:
    DblListNode() : rlink(nullptr), llink(nullptr) {}
    DblListNode(type &d, DblListNode<type>* lk, DblListNode<type>* rk) : data(d), llink(lk), rlink(rk) {}
    DblListNode<type>* GetLeft() const {return llink;}
    DblListNode<type>* GetRight() const {return rlink;}
    void SetData(const type &val) {data = val;}
    
};

template <class type>
class DblList
{
private:
    DblListNode<type>* first;

public:
    DblList() {first = nullptr;}
    DblList(type &val);
    ~DblList();
    int Length() const;
    bool isEmpty() {return first -> rlink == first;}
    DblListNode<type> GetHead() const {return first;}
    void SetHead(DblListNode<type>* ptr) {first = ptr;}
    DblListNode<type>* Search(const type &val);

};

template <class type>
DblList<type>::DblList(type &val)
{
    first = new DblListNode<type>(val);
    first -> rlink = first -> llink = first;
}

template <class type>
DblList<type>::~DblList()
{
    DblListNode<type>* p;
    while (first -> rlink != first)
    {
        p = first -> rlink;
        first -> rlink = p -> rlink;
        delete p;
    }
    delete first;
}
