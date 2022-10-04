# include <iostream>
# include <stack>

using namespace std;

//递归
// int Fib(int n)
// {
//     if (n <= 1) return n;
//     else return Fib(n - 1) + Fib(n - 2);
// }


/*栈辅助
* 通过递归调用树和辅助栈示意图
* 将递归算法转化成迭代法
*/

//Node为数据块，tag = 1表示计算n-1， tag = 2表示计算n - 2
struct Node
{
    int n;
    int tag;
};

int Fib(int n)
{  
    stack<Node> s;
    Node temp;
    int sum = 0;
    do
    {
        while (n > 1)
        {
            temp.n = n;
            temp.tag = 1;
            s.push(temp);
            n--;
        }//Fib(n - 1)
        sum += n;//n must be 1 or 0
        while (!s.empty())
        {
            //if tag == 2,will be pop
            temp = s.top();
            s.pop();
            if (temp.tag == 1)
            {
                temp.tag = 2;
                s.push(temp);
                n = temp.n - 2;
                break;
            }//change to tag = 2
        }
    }while (!s.empty());
    return sum;
}

int main()
{
    std::cout << Fib(5);
}