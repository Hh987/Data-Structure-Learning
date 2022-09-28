# include "LinearList.h"

template <class type>
void ListReverse(List<type> &L)
{
    ListNode<type>* h = L.GetHead(), p, pr;
    h -> link = nullptr;
    p = h -> link;
    while (p != nullptr)
    {
        pr = p;
        p = p -> link;
        pr -> link = h -> link;
        h -> link = pr;
    }
}