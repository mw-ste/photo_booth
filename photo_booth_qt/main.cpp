#include "photobooth.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    try
    {
        QApplication a(argc, argv);
        auto w = new PhotoBooth();
        w->show();
        return a.exec();
    }
    catch (std::exception* e)
    {
        std::cout << "Error: " << e->what() << std::endl;
    }
}
