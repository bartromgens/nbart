QT       -= core gui

TEMPLATE = app

TARGET = nbart

OBJECTS_DIR = tmp/

INCLUDEPATH += ./src/
DEPENDPATH = $$INCLUDEPATH

INCLUDEPATH += /usr/include/boost

LIBS += -L/usr/lib -lboost_system -lboost_thread
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
    src/drawableBody.cpp \
    src/drawable.cpp \
    src/body.cpp \

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
    src/drawableBody.hpp \
    src/body.hpp \

OTHER_FILES += \
    data/whiteball.png \
    data/mars_small.png \
    data/mars.png \
    data/greenball.png \
    data/blurball.png \
    data/black.png \
    settings.txt


