#include "modulemanager_1793.h"

ModuleManager_1793::ModuleManager_1793()
{
    app_dir = new QDir;
}

ModuleManager_1793::~ModuleManager_1793()
{
    delete (app_dir);
    emit send_log_file(LogInfoMsg, "Менеджер модулей уничтожен");
}

void ModuleManager_1793::start()
{
    check_paths();
    check_libs();
    emit send_log_file(LogInfoMsg, "Менеджер модулей запущен");
}

void ModuleManager_1793::check_paths()
{
    QProcess chpaths(this);
    chpaths.start("chmod +x " + app_dir->absolutePath() + "/bin/scripts/chpaths.sh");
    chpaths.waitForFinished();

    chpaths.start("/bin/bash " + app_dir->absolutePath() + "/bin/scripts/chpaths.sh");
    chpaths.waitForReadyRead();
    QString chpathsOutput = QTextCodec::codecForMib(106)->toUnicode(chpaths.readAll());
    qDebug() << chpathsOutput;
    chpaths.waitForFinished();
    if (QString::compare(chpathsOutput, "complete\n", Qt::CaseSensitive))
    {
        emit send_log_file(LogWarningMsg, "Ошибка проверки целостности модулей");
    } else
    {
        emit send_log_file(LogInfoMsg, "Проверка наличия модулей прошла успешно");
    }
}

void ModuleManager_1793::check_libs()
{
    QProcess chlibs(this);
    chlibs.start("chmod +x " + app_dir->absolutePath() + "/bin/scripts/chlibs.sh");
    chlibs.waitForFinished();

    chlibs.start("/bin/bash " + app_dir->absolutePath() + "/bin/scripts/chlibs.sh");
    chlibs.waitForReadyRead();
    QString chlibsOutput = QTextCodec::codecForMib(106)->toUnicode(chlibs.readAll());
    qDebug() << chlibsOutput;
    chlibs.waitForFinished();
    if (QString::compare(chlibsOutput, "complete\n", Qt::CaseSensitive))
    {
        emit send_log_file(LogWarningMsg, "Не удалось корректно выполнить скрипт " + app_dir->absolutePath() + "/bin/Scripts/chlibs.sh");
    } else
    {
        emit send_log_file(LogInfoMsg, "Проверка наличия библиотек прошла успешно");
    }
}
