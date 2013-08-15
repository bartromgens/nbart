#include "mainwindow.h"

#include "mainsimulator.h"
#include "simulatorcontroller.h"

#include <cassert>
#include <iostream>
#include <thread>

MainWindow::MainWindow()
  : QMainWindow(),
    m_mainSimulator(0),
    m_simulatorThread(),
    m_simulatorController(new SimulatorController())
{
  m_textEdit = new QPlainTextEdit;
  setCentralWidget(m_textEdit);

  createActions();
  createMenus();
  createToolBars();

  createMainSimulator();
  //  createStatusBar();

  //  readSettings();
}


MainWindow::~MainWindow()
{
  std::cout << "MainWindow::~MainWindow() - START" << std::endl;

  if (m_simulatorThread->joinable())
  {
    m_simulatorThread->join();
  }

  if (m_mainSimulator)
  {
    delete m_mainSimulator;
    m_mainSimulator = 0;
  }

  std::cout << "MainWindow::~MainWindow() - END" << std::endl;
}


void
MainWindow::createMainSimulator()
{
  assert(!m_mainSimulator);
  m_mainSimulator = new MainSimulator(m_simulatorController);
  m_simulatorThread.reset(new std::thread(&MainSimulator::run, m_mainSimulator));
}


void
MainWindow::slotCloseSimulator()
{
  m_simulatorController->setClose(true);
  m_simulatorThread->join();
}


void
MainWindow::createActions()
{
  m_newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
  m_newAct->setShortcuts(QKeySequence::New);
  m_newAct->setStatusTip(tr("Create a new file"));
  connect(m_newAct, SIGNAL(triggered()), this, SLOT(slotCloseSimulator()));
}


void
MainWindow::createToolBars()
{
  m_fileToolBar = addToolBar(tr("File"));
  m_fileToolBar->addAction(m_newAct);
}


void
MainWindow::createMenus()
{
  m_fileMenu = menuBar()->addMenu(tr("&File"));
  m_fileMenu->addAction(m_newAct);
}
