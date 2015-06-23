#ifndef CHOOSE_SORT_H
#define CHOOSE_SORT_H

/*******************************************************************
  算法原理：每一次从待排序的数据元素中选出最小（或最大）的一个元素，存放在序列的起始
  位置，直到全部待排序的数据元素排完。 对数组A中的n个数进行排序，首先找出A中最小（或
  最大）的元素，将其与A[1]交换，然后找出A中的次最小元素，将其与A[2]交换，对A中的头
  n-1个元素进行这一过程。
 ********************************************************************/

#include <iostream>
using namespace std;

#ifdef __cplusplus
extern "C"{
#endif

void ChooseSort(int *ptr, int length, bool bAsc= true);

void ChooseSort(int *ptr, int length, bool bAsc)
{
    int i,j,key;
    for(j = 0;j < length-1;j++)
    {
        i = j + 1;
        key = *(ptr + j);
        while(i < length)
        {
            int temp;
            if (bAsc)
            {
                if(*(ptr+i) < key)
                {
                    temp = key;
                    key = *(ptr + i);
                    *(ptr + i) = temp;
                }
            } else {
                if(*(ptr + i) > key)
                {
                    temp = key;
                    key = *(ptr + i);
                    *(ptr + i) = temp;
                }
            }
            i++;
        }
        *(ptr + j) = key;
    }
}

#ifdef __cplusplus
}
#endif


#endif // CHOOSE_SORT_H
