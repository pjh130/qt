#ifndef NODE
#define NODE
#include <stdio.h>
#include <QString>
#include "assert.h"

struct NODE1
{
    int id;
    NODE1 *next;
};

NODE1 *createNode(int n)
{
    NODE1 *pHead; //首节点指针
    NODE1 *pRear; //尾节点指针
    NODE1 *pNew; //首节点指针

    for(int i=0; i<n; i++)
    {
        pNew = new NODE1;
        pNew->id = i;
        pNew->next = NULL;
        //初始化头节点
        if (i==0)
        {
            pHead = pNew;
            pRear = pNew;
        } else {
            //在尾部添加新节点
            pRear->next = pNew;
        }
        //尾部节点刷新
        pRear = pNew;
    }
    return pHead;
}

//打印链表中所有节点的数据
void printNode(NODE1 *pHead)
{
    NODE1 *pTemp = pHead;
    assert(pTemp != NULL);
    while (pTemp != NULL)
    {
        printf("%d ",pTemp->id);
        pTemp = pTemp->next;
    }
    printf("\r\n");
}

//查询链表中具有指定ID的节点，并返回此节点指针
NODE1 *searchNode(NODE1 *pHead, int id)
{
    NODE1 *pTemp = pHead;
    while (pTemp != NULL)
    {
        //找到
        if (id == pTemp->id)
        {
            return  pTemp;
        }
        pTemp = pTemp->next;
    }
    return NULL;
}

//删除指定ID的节点，并返回此节点指针
NODE1 *deleteNode(NODE1 *pHead, int id)
{
    NODE1 *pDest = pHead;
    NODE1 *pBefore = NULL;
    while (pDest != NULL)
    {
        ////找到
        if (id == pDest->id)
        {
            //如果是头节点
            if (pDest == pHead)
            {
                pHead = pHead->next;
            } else {
                pBefore->next = pDest->next;
            }
            printf("deleteNode %d \r\n", id);
            return pHead;
        }

        pBefore = pDest;
        pDest = pDest->next;
    }
    printf("can't find delete id: %d\n", id);
    return pHead;
}

//单链表插入(尾部)
NODE1 *insertAppend(NODE1 *pHead, int id)
{
//    return pHead;
    //初始化新节点
    NODE1 *pNew = new NODE1;
    pNew->id = id;
    pNew->next = NULL;

    //如果是空链表
    if (NULL == pHead)
    {
        pHead = pNew;
    } else {
        //遍历到尾部
        NODE1 *pTemp = pHead;
        while (pTemp != NULL)
        {
            //已经到达链表尾部
            if (NULL == pTemp->next)
            {
                pTemp->next = pNew;
                break;
            }
            pTemp = pTemp->next;
        }
    }

    return pHead;
}

//单链表插入(头部)
NODE1 *insertHead(NODE1 *pHead,int id)
{
    //初始化新节点
    NODE1 *pNew = new NODE1;
    pNew->id = id;
    pNew->next = NULL;

    //如果是空链表
    if (NULL == pHead)
    {
        pHead = pNew;
    } else {
        pNew->next = pHead;
        pHead = pNew;
    }

    return pHead;
}

//单链表插入(顺序)
NODE1 *insertSort(NODE1 *pHead,int id, bool bAsc = true)
{
    return pHead;
}

//链表排序
NODE1 *insertSort(NODE1 *pHead, bool bAsc = true)
{
    if (NULL == pHead)
    {
        return pHead;
    }
    //升序排列
    if (true == bAsc)
    {
        NODE1 *pTemp = pHead;
        NODE1 *pTail = NULL;
        NODE1 *pMax = NULL;
        while (pTemp != NULL)
        {
            if (NULL != pTemp->next)
            {
                NODE1 *pNext = pTemp->next;
                if (pNext->id < pTemp->id)
                {

                }
            }


            pTemp = pTemp->next;
        }
    } else{
        //降序排列
    }
}


#endif // NODE

