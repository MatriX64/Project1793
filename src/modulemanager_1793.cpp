#include "include/modulemanager_1793.h"

ModuleManager_1793::ModuleManager_1793()
{

}

ModuleManager_1793::~ModuleManager_1793()
{
    delete_modules();
    emit send_log_file(LogInfoMsg, "Менеджер модулей уничтожен");
}

void ModuleManager_1793::start()
{
    mainModel = model;
    check_paths();
    check_libs();
    emit send_log_file(LogInfoMsg, "Менеджер модулей запущен");
    add_modules();
    set_modules();
}

void ModuleManager_1793::check_paths()
{
    QProcess chpaths(this);
    chpaths.start("chmod +x " + app_dir.absolutePath() + "/bin/scripts/chpaths.sh");
    chpaths.waitForFinished();

    chpaths.start("/bin/bash " + app_dir.absolutePath() + "/bin/scripts/chpaths.sh");
    chpaths.waitForReadyRead();
    QString chpathsOutput = QTextCodec::codecForMib(106)->toUnicode(chpaths.readAll());
    qDebug() << chpathsOutput;
    chpaths.waitForFinished();
    if (QString::compare(chpathsOutput, "complete\n", Qt::CaseSensitive))
    {
        emit send_log_file(LogCriticalMsg, "Ошибка проверки целостности модулей");
        emit quit_critical_sender();
    } else
    {
        emit send_log_file(LogInfoMsg, "Проверка наличия модулей прошла успешно");
    }
}

void ModuleManager_1793::check_libs()
{
    QProcess chlibs(this);
    chlibs.start("chmod +x " + app_dir.absolutePath() + "/bin/scripts/chlibs.sh");
    chlibs.waitForFinished();

    chlibs.start("/bin/bash " + app_dir.absolutePath() + "/bin/scripts/chlibs.sh");
    chlibs.waitForReadyRead();
    QString chlibsOutput = QTextCodec::codecForMib(106)->toUnicode(chlibs.readAll());
    qDebug() << chlibsOutput;
    chlibs.waitForFinished();
    if (QString::compare(chlibsOutput, "complete\n", Qt::CaseSensitive))
    {
        emit send_log_file(LogWarningMsg, "Не удалось корректно выполнить скрипт " + app_dir.absolutePath() + "/bin/Scripts/chlibs.sh");
    } else
    {
        emit send_log_file(LogInfoMsg, "Проверка наличия библиотек прошла успешно");
    }
}

void ModuleManager_1793::add_modules()
{
    wps_attack_module = new WPS_Attack_module("password_attacks|wep/wpa/wpa2_attacks|wps_attack", "WPS_Attack");
    wps_attack_module2 = new WPS_Attack_module("password_attacks|wps_attack", "Una");
}

void ModuleManager_1793::set_modules()
{
    //find max column
    QList<QString> keysList = mainModel->qmlTabView.keys();
    qDebug() << keysList;
}

void ModuleManager_1793::delete_modules()
{
    delete (wps_attack_module);
}
