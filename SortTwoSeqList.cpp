# include <iostream>

using namespace std;

// template <class type>
// void sortTwoSeqList(type A[], type B[], type C[], const int size_A, const int size_B);

// int main()
// {
//     const int aSize = 5;
//     const int bSize = 3;
//     int A[aSize] = {0, 1, 2, 3, 4};
//     int B[bSize] = {3, 4, 5};
//     int C[aSize + bSize];
//     sortTwoSeqList(A, B, C, aSize, bSize);
// }

template <class type>
void sortTwoSeqList(type A[], type B[], type C[], const int size_A, const int size_B)
{
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < size_A || j < size_B)
    {
        if (A[i] < B[j])
        {
            C[k++] = A[i++];     
        }
        else
        {
            C[k++] = B[j++];
        }
    }
    while (i < size_A)
        C[k++] = A[i++];
    while (j < size_B)
        C[k++] = B[j++];
    
    for (int t = 0; t < size_A + size_B; ++t)
    {
        cout << C[t] << ' ';
    }
}