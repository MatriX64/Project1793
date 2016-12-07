#include "core/core_1793.h"

int main(int argc, char *argv[])
{
    QGuiApplication application(argc, argv);

    Core_1793 core(&application);
    core.start();

    return application.exec();
}
