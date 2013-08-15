#include "body.hpp"
#include "drawable.hpp"
#include "drawableBody.hpp"
#include "environment.hpp"
#include "globfunctions.hpp"
#include "gravityfield.hpp"
#include "importsettings.hpp"
#include "initialpattern.hpp"
#include "mainwindow.h"
#include "node.hpp"

#include <QApplication>

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  app.setOrganizationName("Trolltech");
  app.setApplicationName("Application Example");
  MainWindow mainWin;
  mainWin.show();

  app.exec();

  return 0;
}
