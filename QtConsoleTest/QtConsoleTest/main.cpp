#include "QtConsoleTest.h"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    using_tesseract test1;
    test1.find_carnumberver2();
    return a.exec();
} 