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
    PhotoBooth(QWidget *parent = nullptr);
    ~PhotoBooth();

private:
    bool checkCameraAvailability()
    {
        return (QCameraInfo::availableCameras().count() > 0);
    }
};

#endif // PHOTOBOOTH_H
