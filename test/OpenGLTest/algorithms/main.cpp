
#include <QtCore/QCoreApplication>
#include "src/algorithms.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int num[] = {10,5,8,1,9,2,4,11,3,7};
    Algorithms::printArray(num, sizeof(num) / sizeof(int));
    //Algorithms::bubbleSort(num, sizeof(num) / sizeof(int));
    //Algorithms::insertSort(num, sizeof(num) / sizeof(int));
    //Algorithms::selectSort(num, sizeof(num) / sizeof(int));
    //Algorithms::quickSort(num, 0, sizeof(num) / sizeof(int) - 1);
    Algorithms::shellSort(num, sizeof(num) / sizeof(int));

    Algorithms::printArray(num, sizeof(num) / sizeof(int));

    Algorithms::getMaxArray();

    int num2[] = {10,10,1,1,4,4,5,8,8,7,6,5,6};
    Algorithms::getAlone(num2, sizeof(num2) / sizeof(int));


    return a.exec();
}
