# 广义表



## 定义和性质

+ 是线性表的推广，表中的表元可以是一个子表
+ 广义表只有表头和表尾，表头为一个不包含元素的指示节点，表尾为一个子表（注意这里的子表可以只是一个原子节点，或者只有原子节点的链表，或者含有子表的链表），也就是任意层次的广义表都可分为两部分，头节点和尾表
+ 广义表的定义是递归的，因为表中有表
+ 有次序行性
+ 有长度和深度
+ 可递归可共享

## 存储结构表示

+ 标志域 -- utype

> utype = 0 表示头节点
>
> utype = 1 表示原子节点
>
> utype = 2 表示子表点

+ 信息域 -- info

  使用联合union结构保存数据，

  ``` c++
  union 
  {
      int ref;
      T val;
      GenListNode<T>* hlink;
  }info;
  ```

> utype = 0 ref存储头节点被引用次数
>
> utype = 1 info为val
>
> utype = 2 info为hlink存储子表头节点



## 一些类定义

### 节点类

```c++
template <class T>
class GenListNode
{
    friend GenList<T>;

private:
    // int mark;
    int utype;
    GenListNode<T>* tlink;
    union 
    {
        int ref;
        T val;
        GenListNode<T>* hlink;
    }info;

public:
    GenListNode() : mark(0), utype(0), tlink(nullptr), info.ref(0) {}
    GenListNode(GenListNode<T> &RL);
    ~GenListNode() {}

};
```

### 广义表类定义

```c++
template <class T>
class GenList
{
private:
    GenListNode<T>* first;
//    void traverse(GenListNode<T>* ls);
    GenListNode<T>* Copy(GenListNode<T>* ls);
    int Length(GenListNode<T>* ls);
    int Depth(GenListNode<T>* ls);
    bool Equal(GenListNode<T>* s, GenListNode<T>* t);
    void Release(GenListNode<T>* ls);
    void Create(std::istream &in, GenListNode<T>* &ls);

public:
    GenList();
    ~GenList();
    bool Head(GenListNode<T> &h);
    bool Tail(GenList<T> &lt);
    GenListNode<T>* First();
//    void traverse();
    int Depth();
    int Length();
    void Copy(const GenList<T>& R);
    
    friend std::istream operator>>(std::istream &in, GenList<T> &L); 

};
```

### 函数

#### 求第一个节点和尾表

返回广义表的第一个节点和尾节点

```c++
template <class T>
bool GenList<T>::Head(GenListNode<T> &h)			//传参h保存返回的节点
{
    if (first -> tlink == nullptr) return false;	//空链表返回false
    else
    {
        h.info = first -> tlink -> info;
        h.utype = first -> tlink -> utype;
    }
    return true;
}

template <class T>
bool GenList<T>::Tail(GenList<T> &lt)				//lt保存返回的尾表
{
    if (first -> tlink -> tlink == nullptr) return false;		//只有第一个节点说明没有尾表
    else
    {
        lt.first -> utype = 0;
        lt.first -> info.ref = 0;
        lt.first -> tlink = Copy(first -> tlink -> tlink);
    }
    return true;
}
```

#### 递归定义函数

递归定义求长度、深度、复制，清除，判等

```c++
private:
	int Length(GenListNode<T>* ls);
	int Depth(GenListNode<T>* ls);
	bool Equal(GenListNode<T>* s, GenListNode<T>* t);
	void Release(GenListNode<T>* ls);
	void Create(std::istream &in, GenListNode<T>* &ls);

public:
    int Depth();
    int Length();
    void Copy(const GenList<T>& R);
```

##### 长度、深度

公有函数为递归调用入口，私有为递归函数

长度只求当前所咋位置层次长度，原子节点和子表节点一视同仁，递归直到链表尾，每次递归长度加一

深度至少为1（空表也是广义表），每次递归如果为原子节点深度为0，如果为子表节点则深度加一并且递归子表，返回时取最大的深度

##### 相等

+ 都为空表时相等
+ 非空且表元类型相同
  - utype = 1，判断val是否相等，相等递归两表下一节点
  - utype = 2，递归两表子表

##### 复制

每次递归复制一个节点

- utype = 0 or 1， 直接复制节点信息
- utype = 2， 递归复制子表节点

##### 创建

没有给出具体实现，因为个人认为课本中实现太局限，思路：

- 创建原子节点，new一个空间保存原子，并以此节点作为头节点递归调用create
- 创建子表节点
  - 判断子表是否已经存在，存在则ref++,并重新创建一个附加表头同时di递归创建子表（注意这里创建了一个已有的子表）
  - 不存在就info.hlink = new GenListNode<T> 新建一个附加头节点，并以此节点递归调用建立子表
  - 然后建立后续表
  - ）为结束子表创建标志
  - #为空表标志

##### 清除

与上面几个类似，但是要注意如果是附加头节点，要判断其是否为共享子表，即ref是否为1，不是就要--ref，直到ref == 0时才开始删除子表元素（不过这里似乎和前面的创建有冲突，因为共享子表创建时实际是创建了两个一样的子表）

- 结束条件为子表下一节点非空
- 原子节点和普通链表删除方式相同
- 子表节点则递归调用该函数
- 注意要删除头节点







