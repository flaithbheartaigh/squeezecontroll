#ifndef VOLUMEINFO_H
#define VOLUMEINFO_H

#include <QWidget>

namespace Ui {
    class VolumeInfo;
}

class VolumeInfo : public QWidget
{
    Q_OBJECT

public:
    explicit VolumeInfo(QWidget *parent = 0);
    ~VolumeInfo();
    void SetInfo(QString aInf);
    void fadeIn();
    void fadeOut();

private:
    Ui::VolumeInfo *ui;
    int mVolumen;

private slots:
       void setSettingsFrameTrans(int aValue);

};

#endif // VOLUMEINFO_H
