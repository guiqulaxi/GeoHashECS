QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        DisplayGraphicsItem.cpp \
        EntityFu.cpp \
        system/CommunicationSystem.cpp \
        system/DetctionSystem.cpp \
        system/DisplaySystem.cpp \
        system/FusionSystem.cpp \
        system/MovementSystem.cpp \
        system/TrackSystem.cpp \
        Util.cpp \
        main.cpp \
        sample.cpp

TRANSLATIONS += \
    ECS_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    DisplayGraphicsItem.h \
    EntityFu.h \
    component/Ammo.h \
    component/CommunicationDevice.h \
    component/CommunicationEquipment.h \
    component/Display.h \
    component/GCSPosition.h \
    component/MovementFactor.h \
    component/PrevPosition.h \
    system/CommunicationSystem.h \
    component/Damage.h \
    component/DamageSystem.h \
    system/DetctionSystem.h \
    component/Detection.h \
    component/Faction.h \
    component/Fuel.h \
    component/Fusion.h \
    system/DisplaySystem.h \
    system/FusionSystem.h \
    component/Guide.h \
    component/Health.h \
    component/Movement.h \
    Mcomponent/ovementFactor.h \
    system/MovementSystem.h \
    component/Platform.h \
    component/Position.h \
    component/SensorDevice.h \
    component/SensorEquipment.h \
    system/TrackSystem.h \
    Util.h \
    component/WeaponDevice.h \
    component/WeaponEquipment.h


