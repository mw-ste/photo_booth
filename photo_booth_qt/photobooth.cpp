#include "photobooth.h"

PhotoBooth::PhotoBooth(QWidget *parent)
    : QMainWindow(parent)
{
    std::cout << isAnyCameraAvailable() << std::endl;

    const QList<QCameraInfo> cameraInfos = QCameraInfo::availableCameras();

    for (const QCameraInfo &cameraInfo : cameraInfos)
    {
        std::cout << cameraInfo.deviceName().toStdString() << std::endl; // /dev/video0
        std::cout << cameraInfo.description().toStdString() << std::endl; // UVC Camera (046d:0825)
    }

    if(!isAnyCameraAvailable())
    {
        return;
    }

    auto camera = new QCamera(cameraInfos[0]);

    auto viewfinder = new QCameraViewfinder;
    camera->setViewfinder(viewfinder);
    viewfinder->show();

    camera->start(); // to start the viewfinder

    initUI();
}

void PhotoBooth::initUI()
{

}

PhotoBooth::~PhotoBooth()
{
}

