#ifndef GETCOVER_H
#define GETCOVER_H

#include <QObject>

class getCover : public QObject
{
Q_OBJECT
public:
    getCover(QWidget *parent = 0);
    ~getCover();
};

#endif // GETCOVER_H
