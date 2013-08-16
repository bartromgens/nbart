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
MainWindow::createActions()
{
  m_clearAct = new QAction(QIcon(":/images/clear.png"), tr("&Clear"), this);
  connect(m_clearAct, SIGNAL(triggered()), this, SLOT(slotClearSimulator()));

  m_playAct = new QAction(QIcon("./images/icons/play.png"), "&Play", this);
  connect(m_playAct, SIGNAL(triggered()), this, SLOT(slotTogglePlay()));

  m_closeAct = new QAction(QIcon("./images/icons/close.png"), "&Close", this);
  connect(m_closeAct, SIGNAL(triggered()), this, SLOT(slotCloseSimulator()));
}


void
MainWindow::createToolBars()
{
  m_fileToolBar = addToolBar(tr("File"));
  m_fileToolBar->addAction(m_playAct);
  m_fileToolBar->addAction(m_clearAct);
  m_fileToolBar->addAction(m_closeAct);
}


void
MainWindow::createMenus()
{
  m_fileMenu = menuBar()->addMenu(tr("&Simulation"));
  m_fileMenu->addAction(m_playAct);
  m_fileMenu->addAction(m_clearAct);
  m_fileMenu->addAction(m_closeAct);
}


void
MainWindow::slotCloseSimulator()
{
  m_simulatorController->setClose(true);
  m_simulatorThread->join();
}


void
MainWindow::slotTogglePlay()
{
  m_simulatorController->togglePlay();
}


void
MainWindow::slotClearSimulator()
{
  m_simulatorController->setClear(true);
}
