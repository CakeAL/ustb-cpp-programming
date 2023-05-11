//
// Created by cakeal on 2023/5/10.
//
#include <iostream>

using namespace std;

void Qsort(int arr[], int low, int high){
    if (high <= low) return;
    int i = low;
    int j = high;
    int key = arr[low];
    while (true)
    {
        /*从左向右找比key大的值*/
        while (arr[i] <= key)
        {
            i++;
            if (i == high){
                break;
            }
        }
        /*从右向左找比key小的值*/
        while (arr[j] >= key)
        {
            j--;
            if (j == low){
                break;
            }
        }
        if (i >= j) break;
        /*交换i,j对应的值*/
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    /*中枢值与j对应值交换*/
    arr[low] = arr[j];
    arr[j] = key;
    Qsort(arr, low, j - 1);
    Qsort(arr, j + 1, high);
}

int a[500];

int main()
{
    //int a[] = {57, 68, 59, 52, 72, 28, 96, 33, 24};
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        cout << a[i] << " ";
    }
    cout << endl << "after sorting:" << endl;
    Qsort(a, 0, n - 1);/*这里原文第三个参数要减1否则内存越界*/

    for(int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }

    return 0;
}