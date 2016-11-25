#include "include/model_1793.h"

QStringList           Model_1793::networkList;
QMap<QString,QString> Model_1793::qmlTabView;

Model_1793::Model_1793(QObject *parent) : QObject(parent)
{

}

Model_1793::~Model_1793()
{
    Logger_1793::write_log_file(LogInfoMsg, "Модель уничтожена");
}

void Model_1793::start()
{
    Logger_1793::write_log_file(LogInfoMsg, "Модель запущена");
}
