#ifndef ABSTRACTCONTROLLER_H
#define ABSTRACTCONTROLLER_H

#include <QWidget>

class AbstractController: public QWidget {
    Q_OBJECT
public:
    AbstractController(QWidget *parent = nullptr): QWidget(parent) {}

signals:
    void eventTriggered(const QByteArray &data);
    void closeCalled();
};

#endif // ABSTRACTCONTROLLER_H
