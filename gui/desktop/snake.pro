QT += gui core widgets

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ../../brick_game/snake/model_snake.cpp \
        ../../brick_game/tetris/backend.c \
        ../../controller/snake/controller_snake.cpp \
        ../../gui/desktop/view.cpp \
        ../../main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../../brick_game/snake/model_snake.h \
    ../../brick_game/tetris/backend.h \
    ../../brick_game/tetris/structures.h \
    ../../controller/snake/controller_snake.h \
    ../../gui/desktop/view.h
