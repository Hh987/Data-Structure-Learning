# include "LinearList.h"

# include <iostream>
# include <stdlib.h>

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
    if (i < 0 || i > this -> Length())
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
    if (i <= 0 || i > this -> Length()) return false;
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
    ListNode<type>* newListNode;
    type val;
    MakeEmpty();
    std::cin >> val;
    while (val != endTag)
    {
        newListNode = new ListNode<type>(val);
        if (newListNode == nullptr)
        {
            std::cerr << "wrong" << std::endl;
            std::exit(1);
        }
        newListNode -> link = first -> link;
        first -> link = newListNode;
        std::cin >> val;
    }
}

template <class type>
void List<type>::output()
{
    ListNode<type>* current = first -> link;
    while (current != nullptr)
    {
        std::cout << current -> data << std::endl;
        current = current -> link;
    }
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
