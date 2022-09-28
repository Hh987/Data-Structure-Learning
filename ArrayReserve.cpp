# include <iostream>

template <class type>
void arrayReserve(type a[], int size);

int main()
{
    const int arraySize = 5;
    int a[arraySize] = {1, 2, 3, 4, 5};
    arrayReserve(a, arraySize);
    for (int i = 0; i < arraySize; ++i)
        std::cout << a[i] << ' ';

}

template <class type>
void arrayReserve(type a[], int size)
{
    int i = 0, j = size - 1;
    while (i < j)
    {
        type temp = a[i];
        a[i] = a[j];
        a[j] = temp;
        ++i;
        --j;
    }
}