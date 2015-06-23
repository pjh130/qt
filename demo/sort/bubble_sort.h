#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

/***********************************************
 算法原理：
     重复的交换两个反序元素
***********************************************/

#include <iostream>
using namespace std;

#ifdef __cplusplus
extern "C"{
#endif

void PrintInfo(int* pData, int count);
void BubbleSortTail(int *ptr, int length, bool bAsc= true);
void BubbleSortAhead(int *ptr, int length, bool bAsc= true);

//打印
void PrintInfo(int* pData, int count){

    for (int i = 0; i< count; i++) {
        cout << pData[i] << " ";
    }
    cout << endl;
}

//冒泡排序(冒到最后)
void BubbleSortTail(int *ptr, int length, bool bAsc)
{
    for(int i = 0; i < length - 1; i++)
    {
        for(int j = 0; j < length - 1 - i; j++)//把最大的放到最下面 然后再把第二大的放到下面
        {
            if (true == bAsc)
            {
                if((*(ptr + j)- *(ptr + j + 1)) > 0)
                {
                    int temp = *(ptr + j);//如果前面的比后面的大
                    *(ptr + j) = *(ptr + j + 1);//那么就换位置
                    *(ptr + j + 1) = temp;
                }
            }else {
                if((*(ptr + j)- *(ptr + j + 1)) < 0)
                {
                    int temp = *(ptr + j);//如果前面的比后面的大
                    *(ptr + j) = *(ptr + j + 1);//那么就换位置
                    *(ptr + j + 1) = temp;
                }
            }
        }
    }
}

//冒泡排序(冒到最前)
void BubbleSortAhead(int *ptr, int length, bool bAsc)
{
    for(int i = 0; i < length - 1; i++)
    {
        for(int j = length-1; j > i; j--)//把最大的放到最下面 然后再把第二大的放到下面
        {
            if (true == bAsc)
            {
                if((*(ptr + j)- *(ptr + j - 1)) < 0)
                {
                    //那么就换位置
                    int temp = *(ptr + j);
                    *(ptr + j) = *(ptr + j - 1);
                    *(ptr + j - 1) = temp;
                }
            } else {
                if((*(ptr + j)- *(ptr + j - 1)) > 0)
                {
                    //那么就换位置
                    int temp = *(ptr + j);
                    *(ptr + j) = *(ptr + j - 1);
                    *(ptr + j - 1) = temp;
                }
            }
        }
    }
}

#ifdef __cplusplus
}
#endif

#endif // BUBBLE_SORT_H
