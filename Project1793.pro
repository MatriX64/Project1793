TEMPLATE = app

QT += qml quick

CONFIG += c++14

SOURCES += src/core_1793.cpp \
    src/main.cpp \
    src/model_1793.cpp \
    src/modulemanager_1793.cpp \
    src/module_1793.cpp \
    src/wps_attack_module.cpp \
    src/logger_1793.cpp \
    src/initializer_1793.cpp \
    src/dummymodule.cpp

RESOURCES += \
    resfile.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += include/core_1793.h \
    include/model_1793.h \
    include/modulemanager_1793.h \
    include/name_codes_1793.h \
    include/module_1793.h \
    include/wps_attack_module.h \
    include/logger_1793.h \
    include/initializer_1793.h \
    include/dummymodule.h

DISTFILES += \
    qml/WPS_AttackForm.ui.qml \
    qml/main_view.qml \
    qml/WPS_Attack.qml \
    qml/DummyQML.qml
