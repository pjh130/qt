#include <QCoreApplication>

#include "AbstractFactory.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    AbstractFactory* factory = new FactoryA();
    AbstractProduct* product = factory->createProduct();
    product->operation();
    delete product;
    product = NULL;
    delete factory;
    factory = NULL;

    factory = new FactoryB();
    product = factory->createProduct();
    product->operation();
    delete product;
    product = NULL;
    delete factory;
    factory = NULL;

    return a.exec();
}
