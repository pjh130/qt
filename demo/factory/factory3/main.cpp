#include <QCoreApplication>
#include "AbstractFactory.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

#ifdef __cplusplus

printf("This is a c ++ program!\n");

#endif

#ifndef __cplusplus

printf("This is a c program!");

#endif

    AbstractFactory* factory = new Factory1();
    AbstractProductA* productA = factory->createProductA();
    AbstractProductB* productB = factory->createProductB();
    productA->operationA();
    productB->operationB();

    delete factory;
    factory = NULL;
    delete productA;
    productA = NULL;
    delete productB;
    productB = NULL;

    factory = new Factory2();
    productA = factory->createProductA();
    productB = factory->createProductB();
    productA->operationA();
    productB->operationB();

    delete factory;
    factory = NULL;
    delete productA;
    productA = NULL;
    delete productB;
    productB = NULL;

    return a.exec();
}
