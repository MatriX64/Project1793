TEMPLATE = app

QT += qml quick

CONFIG += c++11

SOURCES += main.cpp \
    core_1793.cpp \
    modulemanager_1793.cpp \
    model_1793.cpp

RESOURCES +=

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    core_1793.h \
    modulemanager_1793.h \
    model_1793.h \
    name_codes_1793.h

DISTFILES += \
    main_view.qml

