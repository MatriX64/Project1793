#ifndef MODEL_1793_H
#define MODEL_1793_H

#include "name_codes_1793.h"

#include <QQmlApplicationEngine>

#include <QDebug>

class Model_1793 : public QObject
{
    Q_OBJECT
private:
    QQmlApplicationEngine *main_view;

public:
    Model_1793();
    ~Model_1793();

    void start();

signals:
    void send_log_file(int, const QString&);
    void critical_sender();
    void normal_sender();

public slots:
    void quit_receiver();
};

#endif // MODEL_1793_H
