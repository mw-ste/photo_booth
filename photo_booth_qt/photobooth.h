#ifndef PHOTOBOOTH_H
#define PHOTOBOOTH_H

#include <sstream>
#include <iomanip>
#include <iostream>
#include <chrono>
#include <ctime>
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

        _v4l2loopbackProcess->kill();
    }

private:
    QWidget* _centralWidget;
    QCamera* _camera;
    QPushButton* _captureButton;
    QCameraViewfinder* _viewFinder;
    QProcess* _v4l2loopbackProcess;

    const QString V4l2loopbackCommand = "gphoto2 --stdout --capture-movie | gst-launch-1.0 fdsrc ! decodebin3 name=dec ! queue ! videoconvert ! v4l2sink device=/dev/video0";

    void initUI()
    {
        _centralWidget = new QWidget();
        setCentralWidget(_centralWidget);
        resize(1024, 600);

        //startV4l2Process();

        _viewFinder = new QCameraViewfinder(_centralWidget);
        _viewFinder->resize(1024, 600);

        _captureButton = new QPushButton("Capture Image", _centralWidget);
        connect(_captureButton, &QPushButton::clicked, this, &PhotoBooth::captureImage);

        initLayout();
    }

    void startV4l2Process()
    {
        _v4l2loopbackProcess = new QProcess();
        _v4l2loopbackProcess->start(V4l2loopbackCommand);
        _v4l2loopbackProcess->waitForStarted();

        std::this_thread::sleep_for(std::chrono::seconds(10));

    }

    void initLayout()
    {
        auto mainLayout = new QVBoxLayout();
        mainLayout->addWidget(_viewFinder);
        mainLayout->addWidget(_captureButton);
        _centralWidget->setLayout(mainLayout);
    }

    void initCamera()
    {
//        if(!isAnyCameraAvailable())
//        {
//            throw new std::runtime_error("Could not find any Camera!");
//        }

        const QList<QCameraInfo> cameraInfos = QCameraInfo::availableCameras();
        for (const QCameraInfo &cameraInfo : cameraInfos)
        {
            std::cout << cameraInfo.deviceName().toStdString() << std::endl;  // /dev/video0
            std::cout << cameraInfo.description().toStdString() << std::endl; // UVC Camera (046d:0825)
        }

        //_camera = new QCamera(cameraInfos[0]);
        _camera = new QCamera("/home/michi/photo_booth/fifo.mjpg");
        _camera->setViewfinder(_viewFinder);
        _camera->setCaptureMode(QCamera::CaptureStillImage);
        _camera->start();
    }

    bool isAnyCameraAvailable()
    {
        return (QCameraInfo::availableCameras().count() > 0);
    }

    std::string getTimeStamp()
    {
        std::stringstream image_name_stream;
        auto now_time_point = std::chrono::system_clock::now();
        auto now = std::chrono::system_clock::to_time_t(now_time_point);
        image_name_stream << "test_image_" << std::put_time(std::localtime(&now), "%Y-%m-%d_%H-%M-%S") << ".jpg";
        return image_name_stream.str();
    }

    void printSupportedResolutions(QCameraImageCapture* imageCapture)
    {
        std::cout << "Supported resolutions:" << std::endl;
        auto resolutions = imageCapture->supportedResolutions();
        for(auto resolution : resolutions)
        {
            std::cout << resolution.width() << "x" << resolution.height() << std::endl;
        }
    }

public slots:
    void captureImage()
    {
        std::string image_name = getTimeStamp();
        std::cout << "Capture image: " << image_name << std::endl;

        auto imageCapture = new QCameraImageCapture(_camera);
        printSupportedResolutions(imageCapture);

//        QImageEncoderSettings imageSettings;
//        imageSettings.setCodec("image/jpeg");
//        imageSettings.setResolution(1280, 720);
//        imageCapture->setEncodingSettings(imageSettings);
        connect(imageCapture, &QCameraImageCapture::imageSaved, this, &PhotoBooth::onImageSaved);

        //on half pressed shutter button
        _camera->searchAndLock();

        //on shutter button pressed
        imageCapture->capture(QString::fromStdString(image_name));

        //on shutter button released
        _camera->unlock();
    }

    void onImageSaved(int _, const QString &fileName)
    {
        std::cout << "Image saved as: " << fileName.toStdString() << std::endl;
    }
};

#endif // PHOTOBOOTH_H
