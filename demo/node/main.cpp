#include <QCoreApplication>
#include "node.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //新建链表
    NODE1 *pHead = createNode(10);

    //打印链表
    printNode(pHead);

    //查找链表
    NODE1 *pFind = NULL;
    pFind = searchNode(pHead, 55);
    if (NULL != pFind )
    {
        printf("find %d in the node\r\n", pFind->id);
    } else {
        printf("find NULL\r\n");
    }

    //尾部添加
   pHead = insertAppend(pHead, 10);
   pHead = insertAppend(pHead, 11);
//    NODE1 *pNew = insertAppend(NULL, 10);

    //头部添加
    pHead = insertHead(pHead, -1);
    pHead = insertHead(pHead, -2);

    //删除节点
    pHead = deleteNode(pHead, 5);

    //打印链表
    printNode(pHead);

    NODE1 *pNew = insertAppend(NULL, 100);
    printNode(pNew);
    pNew = deleteNode(pNew, 100);
    printNode(pNew);

    return a.exec();
}
