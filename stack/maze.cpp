# include <iostream>
# include <stack>
# include <fstream>

enum direction
{
    N, NE, E, ES, S, SW, W, WN
};

struct offsets
{
    int a, b;
};//x,y偏移量

struct items
{
    int x, y;
    direction dir;
};//记录正确的路径点坐标和方向

class Maze
{
private:
    offsets move[8];
    int row, col;
    int* mark;
    int* maze;
    const int exit = 2;

public:
    Maze(int r, int c, char* filename);
    ~Maze() {delete[] mark, maze;}
    void Path();//非递归算法
    int seek(int x, int y);//递归算法

};

Maze::Maze(int r, int c, char* filename) : row(r), col(c)
{
    //偏移量初始化
    move[N].a = -1; move[N].b = 0;
    move[NE].a = -1; move[NE].b = 1;
    move[E].a = 0; move[E].b = 1;
    move[ES].a = 1; move[ES].b = 1;
    move[S].a = 1; move[S].b = 0;
    move[SW].a = 1; move[SW].b = -1;
    move[W].a = 0; move[W].b = -1;
    move[WN].a = -1; move[WN].b = -1;

    mark = new int[(row + 2) * (col + 2)];
    maze = new int[(row + 2) * (col + 2)];
    //输入迷宫
    std::ifstream fin;
    fin.open(filename);
    if (!fin) std::cerr << "wrong" << std::endl;
    for (int i = 0; i < row + 2; ++i)
    {
        for (int j = 0; j < col + 2; ++j)
        {
            fin >> maze[(row + 2) * i + j];
            mark[(row + 2) * i + j] = 0;
        }
    }
    fin.close();
}

void Maze::Path()
{
    //把入口压入栈，
    mark[row + 2] = 1; //mark[1][1] = 1
    std::stack<items> s;
    items temp;
    temp.x = 1;
    temp.y = 1;
    temp.dir = N;
    s.push(temp);
    int i, j, g, h, d;
    while (!s.empty())
    {
        //遇到死路就退栈，dir记录当前位置没走过的下一个方向
        temp = s.top();
        s.pop();
        i = temp.x;
        j = temp.y;
        d = temp.dir;
        while (d < 8)
        {
            g = i + move[d].a;
            h = j + move[d].b;
            if (maze[g * row + h] == exit)
            {
                //输出路径
                std::cout << g << ',' << h << " <- ";
                std::cout << i << ',' << j << " <- ";
                while (!s.empty())
                {
                    std::cout << s.top().x << ',' << s.top().y << " <- ";
                    s.pop();
                }
                std::cout << " begin" << std::endl;
                return;
            }//find the exit
            if (maze[g * row + h] == 0 && !mark[g * row + h])
            {
                //走到i，j位置标注方向的位置g，h，并标记mark
                mark[g * row + h] = 1;
                temp.x = i;
                temp.y = j;
                temp.dir = (direction)(d + 1);//把i，j位置方向更新到下一个
                s.push(temp);
                i = g;
                j = h;
                d = 0;
            }
            else d++;//当前方向是墙则换下一个方向
        }//重复进行直到8个方向都没有路
    }
    std::cout << "No path in Maze" << std::endl;
}   

// int Maze::seek(int x, int y)
// {
//     int i, g, h, d;
//     d = 0;
//     if (maze[x * row + y] == exit) return 1;
//     for (i = 1; i < 8; ++i)
//     {
//         g = x + move[d].a;
//         h = y + move[d].b;
//         d = i;
//         if (maze[g * row + h] == 0 && !mark[g * row + h])
//         {
//             mark[g * row + h] = 1;
//             if (seek(g, h))
//             {
//                 std::cout << g << ',' << h << ' ';
//                 return 1;
//             }
//         }
//     }
//     if (x == 1 && y == 1)
//     {
//         std::cout << "No path in Maze" << std::endl;
//         return 0;
//     }
//     return 0;
// }

int main()
{
    Maze m(6, 10, "maze.txt");
    int i = m.seek(1, 1);
}