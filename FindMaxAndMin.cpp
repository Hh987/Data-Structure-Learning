# include <iostream>

using namespace std;

template <class type>
void findMaxAndMin(type A[], const int size);

int count = 0;

int main()
{
    const int arraySize = 1;
    int A[10] = {5, 4, 9, 8, 3, 2, 1, 6, 7, 0};
    findMaxAndMin(A, arraySize);
}

template <class type>
void findMaxAndMin(type A[], const int size)
{
    count = 0;
    if (size == 1 || size == 0)
    {
        std::cerr << "wrong" << std::endl;
        std::exit(1);
    }
    type min_val, max_val;
    min_val = max_val = A[0];
    int i = 1;
    while (i < size)
    {
        if (max_val < A[i])
        {
            max_val = A[i];
            ++count;
        }
        else
        {
            min_val = min(min_val, A[i]);
            ++count;
        }
        ++i;
    }
    
    std:: cout << max_val << ' ' << min_val << std::endl;
    std::cout << count;
}

// template <class type>
// void findMaxAndMin(type A[], const int size)
// {
//     count = 0;
//     if (size == 1 || size == 0)
//     {
//         std::cerr << 'wrong' << std::endl;
//         std::exit(1);
//     }
//     int mid = size / 2;
//     type max_val, min_val;
//     max_val = A[mid];
//     min_val = A[mid];
//     int left = mid - 1, right = mid;
    
//     while (left > 0 && right < size - 1)
//     {
//         if (A[left] < min_val)
//         {
//             min_val = A[left];
//             ++count;
//         }
//         else
//         {
//             max_val = max(max_val, A[left]);
//             ++count;
//         }
//         if (A[right] > max_val)
//         {
//             max_val = A[right];
//             ++count;
//         }
//         else
//         {
//             min_val = min(min_val, A[right]);
//             ++count;
//         }
        
//         --left;
//         ++right;
//     }
//     if (right == size - 1)
//     {
//         max_val = max(max_val, A[right]);
//         min_val = min(min_val, A[right]);
//         count += 2;
//     }
//     std:: cout << max_val << ' ' << min_val << std::endl;
//     std::cout << count;
// }