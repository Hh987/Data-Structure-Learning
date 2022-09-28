# include "LinearList.h"

template <class type>
void SortDbList(DblList<type> &Dbl)
{
    DblListNode<type>* h = Dbl.GetHead();
    DblListNode<type>* p, q, cur, t;
    int len = Dbl.Length();
    p = h;
    cur = p -> llink;
    q = cur -> llink;
    while (--len)
    {
        while (q != t)
        {
            if (cur -> data < q -> data)
            {
                cur -> llink = q -> llink;
                q -> llink = cur;
                p -> llink = q;
            }
            q = q -> llink;
            cur = cur -> llink;
            p = p -> llink;
        }
    }
}