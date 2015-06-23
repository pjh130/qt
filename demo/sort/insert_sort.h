#ifndef INSERT_SORT_H
#define INSERT_SORT_H

/*************************************************************************************************
  算法原理： 插入排序的基本思想是：每步将一个待排序的纪录，按其关键码值的大小插入前面已经排序的文件中适当位置上，直到全部
  插入完为止。与和很多人打牌的时候整理手中的牌的做法差不多。开始模牌时，左手是空的，然后模牌，并将它插入左手一把牌中的正确
  位置上，为了找到这张牌的正确位置，将它与左手中的每一张牌从右向左的进行比较，无论什么时候，左手中的牌都是排好序的。
  平均来说插入排序算法的时间复杂度为O(n^2）
*************************************************************************************************/

#include <iostream>
using namespace std;

#ifdef __cplusplus
extern "C"{
#endif

void InsertSort(int *ptr, int length, bool bAsc= true);

void InsertSort(int *ptr, int length, bool bAsc)
{
    //    int i,j,key;
    //    for(j = 1; j < length; j++)
    //    {
    //        key = *(ptr + j);
    //        i = j-1;
    //        if (true == bAsc)
    //        {
    //            while((i > 0 && *(ptr + i) > key))
    //            {
    //                *(ptr + i + 1) = *(ptr + i);
    //                i--;
    //            }
    //            *(ptr + i + 1) = key;
    //        } else {
    //            return;
    //            while((i > 0 && *(ptr + i) <= key))
    //            {
    //                *(ptr + i) = *(ptr + i + 1);
    //                i--;
    //            }
    //            *(ptr + i ) = key;
    //        }
    //    }
    for (int i = 1; i < length; i++)
    {
//        if (ptr[i - 1] > ptr[i])
//        {
            int temp = ptr[i];
            int j = i;
            while (j > 0 && ptr[j - 1] > temp)
            {
                ptr[j] = ptr[j - 1];
                j--;
            }
            ptr[j] = temp;
//        }
    }
}

#ifdef __cplusplus
}
#endif


#endif // INSERT_SORT_H
