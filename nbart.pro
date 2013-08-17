QT       += core gui

TEMPLATE = app

TARGET = nbart

OBJECTS_DIR = tmp/

INCLUDEPATH += ./src/
DEPENDPATH = $$INCLUDEPATH

INCLUDEPATH += /usr/include/boost

LIBS += -L/usr/lib
LIBS += -lSDL_image -lSDL -lSDL_ttf

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += \
    src/trajectory.cpp \
    src/SDL_rotozoom.cpp \
    src/SDL_gfxPrimitives.cpp \
    src/node.cpp \
    src/main.cpp \
    src/integrator.cpp \
    src/importsettings.cpp \
    src/globfunctions.cpp \
    src/environment.cpp \
    src/drawable.cpp \
    src/body.cpp \
    src/initialpattern.cpp \
    src/gravityfield.cpp \
    src/mainwindow.cpp \
    src/mainsimulator.cpp \
    src/simulatorcontroller.cpp

HEADERS += \
    src/drawable.hpp \
    src/trajectory.hpp \
    src/SDL_rotozoom.h \
    src/SDL_gfxPrimitives_font.h \
    src/SDL_gfxPrimitives.h \
    src/node.hpp \
    src/integrator.hpp \
    src/importsettings.hpp \
    src/globfunctions.hpp \
    src/environment.hpp \
    src/body.hpp \
    src/initialpattern.hpp \
    src/gravityfield.hpp \
    src/mainwindow.h \
    src/mainsimulator.h \
    src/simulatorcontroller.h

OTHER_FILES += \
    data/whiteball.png \
    data/mars_small.png \
    data/mars.png \
    data/greenball.png \
    data/blurball.png \
    data/black.png \
    settings.txt \
    data/icons/media-playback-stop.png \
    data/icons/media-playback-start.png \
    data/icons/media-playback-pause.png \
    data/icons/edit-clear.png \
    data/icons/document-open.png \
    data/icons/process-stop.png


