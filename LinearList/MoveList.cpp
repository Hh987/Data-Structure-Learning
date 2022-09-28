# include "LinearList.h"
# include <iostream>

using namespace std;

template <class type>
void moveLeft(List<type> &L, ListNode<type>* pr, ListNode<type>* p, int k);
template <class type>
void moveRight(List<type> &L, ListNode<type>* pr, ListNode<type>* p, int k);

template <class type>
void moveLeft(List<type> &L, ListNode<type>* pr, ListNode<type>* p, int k)
{
    ListNode<type>* q;
    q = p;
    p = pr;
    pr = q;
    while (p != nullptr && k > 0)
    {
        q = p -> link;
        p -> link = pr;
        pr = p;
        p = q;
        k--;
    }
}

template <class type>
void moveRight(List<type> &L, ListNode<type>* pr, ListNode<type>* p, int k)
{
    ListNode<type>* q;
    while (k > 0 && p != nullptr)
    {
        q = p -> link;
        p -> link = pr;
        pr = p;
        p = q;
        --k;
    }
}