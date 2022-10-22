#pragma once

#include <string>
#include <iostream>

template <class T>
class GenList;
 
template <class T>
class GenListNode
{
    friend GenList<T>;

private:
    // std::string name;        //用于习题遍历算法
    // int mark;                //用于习题遍历算法
    int utype;
    GenListNode<T>* tlink;
    union 
    {
        int ref;
        T val;
        GenListNode<T>* hlink;
    }info;

public:
    GenListNode() : utype(0), tlink(nullptr) { info.ref = 0;}
    GenListNode(GenListNode<T> &RL);
    ~GenListNode() {}

};

template <class T>
class GenList
{
private:
    GenListNode<T>* first;
    void traverse(GenListNode<T>* ls);
    GenListNode<T>* Copy(GenListNode<T>* ls);
    int Length(GenListNode<T>* ls);
    int Depth(GenListNode<T>* ls);
    bool Equal(GenListNode<T>* s, GenListNode<T>* t);
    void Release(GenListNode<T>* ls);
    void Create(std::istream &in, GenListNode<T>* &ls, SeqList<T> &name, SeqList<GenListNode<T>*> &address);

public:
    GenList();
    ~GenList();
    bool Head(GenListNode<T> &h);
    bool Tail(GenList<T> &lt);
    GenListNode<T>* First();
    void traverse();
    int Depth();
    int Length();
    void Copy(const GenList<T>& R);
    
    friend std::istream operator>>(std::istream &in, GenList<T> &L); 

};