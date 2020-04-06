#ifndef PHOTOBOOTH_H
#define PHOTOBOOTH_H

#include <iostream>
#include <QMainWindow>
#include <QtMultimedia>
#include <QtMultimediaWidgets>

class PhotoBooth : public QMainWindow
{
    Q_OBJECT

public:
    PhotoBooth(QWidget *parent = nullptr) : QMainWindow(parent)
    {
        initUI();
        initCamera();
    }


    ~PhotoBooth()
    {
        _camera->stop();
    }

private:
    QWidget* _centralWidget;
    QCamera* _camera;
    QPushButton* _captureButton;
    QCameraViewfinder* _viewFinder;

    void initUI()
    {
        _centralWidget = new QWidget();
        setCentralWidget(_centralWidget);

        _captureButton = new QPushButton("Capture Image", _centralWidget);

        _viewFinder = new QCameraViewfinder(_centralWidget);
        _viewFinder->resize(1024, 600);
        connect(_captureButton, &QPushButton::clicked, this, &PhotoBooth::captureImage);

        auto mainLayout = new QVBoxLayout();
        mainLayout->addWidget(_viewFinder);
        mainLayout->addWidget(_captureButton);
        _centralWidget->setLayout(mainLayout);
    }

    void initCamera()
    {
        if(!isAnyCameraAvailable())
        {
            throw "Could not find any Camera!";
        }

        const QList<QCameraInfo> cameraInfos = QCameraInfo::availableCameras();
        for (const QCameraInfo &cameraInfo : cameraInfos)
        {
            std::cout << cameraInfo.deviceName().toStdString() << std::endl;  // /dev/video0
            std::cout << cameraInfo.description().toStdString() << std::endl; // UVC Camera (046d:0825)
        }

        _camera = new QCamera(cameraInfos[0]);
        _camera->setViewfinder(_viewFinder);
        _camera->setCaptureMode(QCamera::CaptureStillImage);
        _camera->start();
    }

public slots:
    void captureImage()
    {
        std::cout << "Capture image!" << std::endl;

        auto imageCapture = new QCameraImageCapture(_camera);

        //on half pressed shutter button
        _camera->searchAndLock();

        //on shutter button pressed
        imageCapture->capture("test_image.jpg");

        //on shutter button released
        _camera->unlock();
    }

    bool isAnyCameraAvailable()
    {
        return (QCameraInfo::availableCameras().count() > 0);
    }
};

#endif // PHOTOBOOTH_H
