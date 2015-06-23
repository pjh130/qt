#include <QCoreApplication>
#include <iostream>
#include "bubble_sort.h"
#include "choose_sort.h"
#include "insert_sort.h"
#include "quick_sort.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int data[] = {6, 10, 7, 8, 4, 9, 5};

    PrintInfo(data, 7);

//    BubbleSortTail(data, 7);
//    BubbleSortAhead(data, 7, true);

//    ChooseSort(data, 7);
//    ChooseSort(data, 7, false);

//    InsertSort(data, 7, true);
    InsertSort(data, 7, false);

//    QuickSort(data, 0, 7, true);
//    QuickSort(data, 0, 7, false);

    PrintInfo(data, 7);

    return a.exec();
}

