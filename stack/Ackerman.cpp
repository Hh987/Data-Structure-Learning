# include <stack>
# include <iostream>

using namespace std;

//递归算法
// int akm(int m, int n)
// {
//     if (m == 0) return n + 1;
//     else if (n == 0) return akm(m - 1, 1);
//     else return akm(m - 1, akm(m, n - 1));
// } 

//递归栈辅助
struct Node
{
    int n, m;
};

// int akm(int m, int n)
// {
//     stack<Node> s;
//     Node w;
//     w.m = m;
//     w.n = n;
//     s.push(w);
//     int res = 0;
//     do
//     {   
//         while (s.top().m > 0)
//         {
//             while (s.top().n > 0)
//             {
//                 w.m = s.top().m;
//                 w.n = s.top().n - 1;
//                 s.push(w);
//             }//akm(m, n-1)
//             w.m = s. top().m - 1;
//             w.n = 1;
//             s.pop();
//             s.push(w);
//         }//akm(m-1,1)
//         res = s.top().n + 1;
//         s.pop();
//         if (!s.empty())
//         {
//             w.m = s.top().m - 1;
//             w.n = res;
//             s.pop();
//             s.push(w);
//         }//akm(m-1, akm(m, n-1))
//     } while (!s.empty());
//     return res;
// }

int akm(int m, int n)
{
    int res;
    Node temp;
    stack<Node> s;
    temp.m = m;
    temp.n = n;
    s.push(temp);
    do
    {
        while (s.top().m > 0)
        {
            while (s.top().n > 0)
            {
                temp = s.top();
                temp.n -= 1;
                s.push(temp);
            }
            temp = s.top();
            s.pop();
            temp.n = 1;
            temp.m -= 1;
            s.push(temp);
        }
        res = s.top().n + 1;
        s.pop();
        if (!s.empty())
        {
            temp = s.top();
            s.pop();
            temp.n = res;
            temp.m -= 1;
            s.push(temp);
        }
    }while (!s.empty());
    return res;
}

int main()
{
    cout << akm(2, 1);
}