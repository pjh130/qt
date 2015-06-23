#ifndef QUICK_SORT_H
#define QUICK_SORT_H

/*************************************************************************************************
  该方法的基本思想是：
  1．先从数列中取出一个数作为基准数。
  2．分区过程，将比这个数大的数全放到它的右边，小于或等于它的数全放到它的左边。
  3．再对左右区间重复第二步，直到各区间只有一个数。

快速排序采用的是分治法，其平均时间复杂度为O（nlogn）
一趟快速排序的算法是[1]：
1）设置两个变量I、J，排序开始的时候：I=0，J=N-1；
2）以第一个数组元素作为关键数据，赋值给key，即 key=A[0]；
3）从J开始向前搜索，即由后开始向前搜索（J=J-1即J--），找到第一个小于key的值A[j]，A[j]与A[i]交换；
4）从I开始向后搜索，即由前开始向后搜索（I=I+1即I++），找到第一个大于key的A[i]，A[i]与A[j]交换；
5）重复第3、4、5步，直到 I=J； (3,4步是在程序中没找到时候j=j-1，i=i+1，直至找到为止。找到并交换的时候i， j指针位置不变。另外当i=j这过程一定正好是i+或j-完成的最后另循环结束。）
*************************************************************************************************/

#include <iostream>
using namespace std;

#ifdef __cplusplus
extern "C"{
#endif

void QuickSort1(int *ptr, int left, int right, bool bAsc= true);
void QuickSort2(int *a, int left, int right, bool bAsc= true);
void QuickSort3(int a[], int low, int high, bool bAsc= true);

void QuickSort1(int *ptr, int left, int right, bool bAsc)
{
    if(left<right)
    {
        int i = left;
        int j = right;
        int x = *(ptr+i);

        while(i<j)
        {
            while(i<j&&*(ptr+j)>x)
                j--;
            if(i<j){
                *(ptr+i) = *(ptr+j);
                i++;
            }
            while(i<j&&*(ptr+i)<x)
                i++;
            if(i<j){
                *(ptr+j) = *(ptr+i);
                j--;
            }
        }
        *(ptr+i) = x;
        QuickSort1(ptr, left, i-1);
        QuickSort1(ptr, i+1, right);
    }
}

void QuickSort2(int *a, int left, int right, bool bAsc)
{
    //如果左边索引大于或者等于右边的索引就代表已经整理完成一个组了
    if(left >= right)
    {
        return ;
    }
    int i = left;
    int j = right;
    int key = a[left];

    //控制在当组内寻找一遍
    while(i < j)
    {
        //而寻找结束的条件就是，1，找到一个小于或者大于key的数（大于或小于取决于你想升
        //序还是降序）2，没有符合条件1的，并且i与j的大小没有反转
        while(i < j && key <= a[j])
        {
            /*向前寻找*/
            j--;
        }
        a[i] = a[j];
        //找到一个这样的数后就把它赋给前面的被拿走的i的值（如果第一次循环且key是
        //a[left]，那么就是给key）
        //这是i在当组内向前寻找，同上，不过注意与key的大小关系停止循环和上面相反，
        //因为排序思想是把数往两边扔，所以左右两边的数大小与key的关系相反
        while(i < j && key >= a[i])
        {
            i++;
        }
        a[j] = a[i];
    }
    //当在当组内找完一遍以后就把中间数key回归
    a[i] = key;

    //最后用同样的方式对分出来的左边的小组进行同上的做法
    QuickSort2(a, left, i - 1);

    //用同样的方式对分出来的右边的小组进行同上的做法
    QuickSort2(a, i + 1, right);

    //当然最后可能会出现很多分左右，直到每一组的i = j 为止
}

void QuickSort3(int a[], int low, int high, bool bAsc)
{
    if(low >= high)
    {
        return;
    }
    int first = low;
    int last = high;
    int key = a[first];/*用字表的第一个记录作为枢轴*/

    while(first < last)
    {
        while(first < last && a[last] >= key)
        {
            --last;
        }

        a[first] = a[last];/*将比第一个小的移到低端*/

        while(first < last && a[first] <= key)
        {
            ++first;
        }

        a[last] = a[first];
        /*将比第一个大的移到高端*/
    }
    a[first] = key;/*枢轴记录到位*/
    QuickSort3(a, low, first-1);
    QuickSort3(a, first+1, high);
}

#ifdef __cplusplus
}
#endif

#endif // QUICK_SORT_H
