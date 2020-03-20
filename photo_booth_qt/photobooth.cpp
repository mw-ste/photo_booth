#include "photobooth.h"

PhotoBooth::PhotoBooth(QWidget *parent)
    : QMainWindow(parent)
{
    std::cout << checkCameraAvailability() << std::endl;
}

PhotoBooth::~PhotoBooth()
{
}

