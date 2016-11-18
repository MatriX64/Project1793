#include "include/core_1793.h"
#include "include/app_controller_1793.h"

int main(int argc, char *argv[])
{
    AppController_1793::application = new QGuiApplication(argc, argv);

    Core_1793 core;
    core.start();

    return AppController_1793::application->exec();
}
