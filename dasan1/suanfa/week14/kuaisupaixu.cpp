#include <iostream>
#include <vector>
using namespace std;

int part(int *v, int low, int height)
{
    int i = low, j = height, key = v[low];
    while(i < j)
    {
        while(i < j && v[j] > key)
        {
            j--;
        }
        if(i < j)
        {
            auto temp = v[i];
            v[i] = v[j];
            v[j] = temp;
            i++;
        }

        while(i < j && v[i] <= key)
        {
            i++;
        }
        if(i < j)
        {
            auto temp = v[i];
            v[i] = v[j];
            v[j] = temp;
            j--;
        }
    }

    return i;
}

void Quicksort(int *v, int low, int height)
{
    int mid;
    if(low < height)
    {
        mid = part(v, low, height);
        Quicksort(v, low, mid - 1);
        Quicksort(v, mid + 1, height);
    }
}

int length(int *v)
{
    // return sizeof(v) / sizeof(&v);
    cout << sizeof(v) << endl;
    cout << sizeof(&v) << endl;
    return 0;
}

int main()
{
    int v[] = {3, 2, 9, 1, 4, 0};
    int v_length = sizeof(v) / sizeof(&v);
    // // int v_length = length(v);

    Quicksort(v, 0, v_length - 1);
    for(int i = 0; i < v_length; i++)
    {
        cout << v[i] << endl;
    }

    // float a = 3000;
    // float b = 3500;
    // swap(a, b);

    // cout << a << endl;
    // cout << b << endl;


    return 0;

}