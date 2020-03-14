#ifndef PHOTOBOOTH_H
#define PHOTOBOOTH_H

#include <QMainWindow>

class PhotoBooth : public QMainWindow
{
    Q_OBJECT

public:
    PhotoBooth(QWidget *parent = nullptr);
    ~PhotoBooth();
};
#endif // PHOTOBOOTH_H
