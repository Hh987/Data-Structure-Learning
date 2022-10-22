#include "GeneralizedList.h"
#include <assert.h>

template <class T>
GenListNode<T>::GenListNode(GenListNode<T> &RL)
{
    // mark = RL.mark;
    utype = RL.utype;
    info = RL.info;
    tlink = RL.tlink;
}

template <class T>
void GenList<T>::Create(std::istream &in, GenListNode<T>* &ls, SeqList<T> &name, SeqList<GenListNode<T>*> &address)
// name 保存表名，address保存表面对应地址
{
    T chr;
    in >> chr;
    if (isalpha(chr) && isupper(chr) || chr == '(')			//大写字母表示输入为子表名，（表示进入子表
    {
        ls = new GenListNode<T>;
        ls -> utype = 2;
        if (isalpha(chr) && isupper(chr))                   //处理表名
        {
            int n = name.Length();
            int m = L1.Search(chr);
            if (m != 0)                                     //有该表存在
            {
                GenListNode<T>* p = L2.Locate(m);
                p -> info.ref++;
            }
            else 
            {
                L1.insert(n, chr);
                L2.insert(n, ls);
            }
            cin >> chr;
            if (chr != '(') exit(1);
        }
        ls -> info.hlink = new GenListNode<T>;              //创建附加头节点
        ls -> info.hlink -> utype = 0;  
        ls -> info.hlink -> info.ref = 1;
        Create(in, ls -> info.hlink -> tlink, name, address);   //创建后续子表
        Create(in, ls -> tlink, name, address);                      //创建后续表
	}
    else if (isalpha(chr) && islower(chr))                  //小写字母创建原子表元
    {
        ls = new GenListNode<T>;
        ls -> utype = 1;
        ls -> info.val = chr;
        Create(in, ls -> tlink, name, address);
    }
    else if (chr == ',') Create(in, ls, name, address);      //，跳过
    else if (chr == ')') ls -> tlink = nullptr;              //结束子表创建
    else if (chr == '#') ls = nullptr;                       //创建空表
}

template <class T>
GenList<T>::GenList()
{   
    first = new GenListNode<T>;
    assert(first != nullptr);
}

template <class T>
GenList<T>::~GenList()
{
    Release(first);
}

template <class T>
void GenList<T>::Release(GenListNode<T>* ls)
{
    ls -> info.ref--;
    if (ls -> info.ref == 0)
    {
        GenListNode<T>* q;
        while (ls -> tlink != nullptr)
        {
            q = ls -> tlink;
            if (q -> utype == 2)
            {
                Release(ls -> info.hlink);
                if (q -> info.hlink -> info.ref <= 0)
                    delete q -> info.hlink;             //删除头节点
            }
            ls -> tlink = q -> tlink;
            delete q;
        }   
    }
}

template <class T>
bool GenList<T>::Head(GenListNode<T> &h)
{
    if (first -> tlink == nullptr) return false;
    else
    {
        h.info = first -> tlink -> info;
        h.utype = first -> tlink -> utype;
    }
    return true;
}

template <class T>
bool GenList<T>::Tail(GenList<T> &lt)
{
    if (first -> tlink -> tlink == nullptr) return false;
    else
    {
        lt.first -> utype = 0;
        lt.first -> info.ref = 0;
        lt.first -> tlink = Copy(first -> tlink -> tlink);
    }
    return true;
}

template <class T>
GenListNode<T>* GenList<T>::First()
{
    if (first -> tlink == nullptr) return nullptr;
    else return first -> tlink;
}

template <class T>
void GenList<T>::Copy(const GenList<T>& R)
{
    first = Copy(R.first);
}

template <class T>
GenListNode<T>* GenList<T>::Copy(GenListNode<T>* ls)
{
    GenListNode<T>* q;
    if (ls != nullptr)              //结束条件
    {   
        q = new GenListNode<T>;
        q -> utype = ls -> utype;
        switch (ls -> utype)
        {
        case 0: q -> info.ref = ls -> info.ref; break;
        case 1: q -> info.val = ls -> info.val; break;
        case 2: q -> info.hlink = Copy(ls -> info.hlink); break;    //递归复制子表
        }
        q -> tlink = Copy(ls ->tlink);                              //复制当前表下一个表元
    }
    return q;
}

    template <class T>
    int GenList<T>::Length()
    {
        return Length(first);
    }

    template <class T>
    int GenList<T>::Length(GenListNode<T>* ls)
    {
        if (ls -> tlink != nullptr) return 1 + Length(ls -> tlink);
        else return 0;
    }

template <class T>
int GenList<T>::Depth()
{
    return Depth(first);
}

template <class T>
int GenList<T>::Depth(GenListNode<T>* ls)
{
    //空表深度为1
    if (ls -> tlink == nullptr) return 1;
    GenListNode<T>* temp = ls -> tlink;
    int m = 0;
    int n;
    while (temp != nullptr)         //temp在顶层搜索
    {
        if (temp -> utype == 2)     //utype=2表示子表
        {
            n = Depth(temp -> info.hlink);
            m = std::max(n, m);          //取最大深度
        }
        temp = temp -> tlink;
    }
    return m + 1;                   //+1为顶层表，即至少有1层
}

template <class T>
bool GenList<T>::Equal(GenListNode<T>* s, GenListNode<T>* t)
{
    // int x;
    if (s -> tlink == nullptr && t -> tlink == nullptr) return true; //s,t都为空表相等
    if (s -> tlink != nullptr && t -> tlink != nullptr /
        s -> tlink -> utype == t -> tlink -> utype)                  //s,t的节点类型相同
    {
        if (s -> tlink -> utype == 1)                               //原子节点
        {
            if (s -> tlink -> info.val == t -> tlink -> info.val)
                return Equal(s -> tlink, t -> tlink);
        }   
        else if (s -> tlink ->utype == 2)
        {
            return Equal(s -> tlink -> info.hlink, t -> tlink -> info.hlink);
        }
    }
    return false;
}

//递归算法
// template <class T>
// void GenList<T>::traverse(GenListNode<T>* ls)
// {
//     if (ls != nullptr)
//     {
//         ls -> mark = 1;
//         if (ls -> utype == 0)
//             std::cout << name << '(';
//         else if (ls -> utype == 1)
//         {
//             std::cout << ls -> info.val;
//             if (ls -> tlink != nullptr) std::cout << ',';
//         }
//         else if (ls -> utype == 2)
//         {
//             if (ls -> info.hlink -> mark == 0)
//                 traverse(ls -> info.hlink);
//             else std::cout << name;
//         }
//         traverse(ls -> tlink);
//     }
//     std::cout << ')';
// }

//栈辅助算法
// template <class T>
// void GenList<T>::traverse(GenListNode<T>* ls)
// {
//     std::stack<GenListNode<T>*> s;
//     ls -> mark = 1;
//     s.push(ls -> tlink);
//     std::cout << ls -> name << '(';
//     ls = ls -> tlink;
//     while (!s.empty())
//     {
//         while (ls -> utype == 1)
//         {
//             std::cout << ls -> info.val;
//             ls = ls -> tlink;
//             if (ls != nullptr) std::cout << ',';
//             else break;
//         }
//         if (ls -> utype == 2)
//         {
//             if (ls -> info.hlink -> mark == 1)
//                 std::cout << ls -> info.hlink -> name << ',';
//             else
//             {
//                 ls -> info.hlink -> mark = 1;
//                 s.push(ls -> tlink);
//                 ls = ls -> info.hlink -> tlink;
//                 std::cout << ls -> name << '(';
//             }
//         }
//         if (ls == nullptr)
//         {
//             std::cout << ')';
//             ls = s.top();
//             s.pop();
//             if (!s.empty()) std::cout << ',';
//         }
//     }  
// }

// template <class T>
// void GenList<T>::traverse()
// {
//     traverse(first);
// }

// template <class T>
// std::istream operator>>(std::istream &in, GenList<T> &L)
// {

// }
