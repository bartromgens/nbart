#include "mainwindow.h"

#include "mainsimulator.h"
#include "simulatorcontroller.h"
#include "simulationsettingswidget.h"

#include <QAction>
#include <QMenuBar>
#include <QToolBar>

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
  SimulationSettingsWidget* simulationSettingsWidget = new SimulationSettingsWidget(m_simulatorController, this);
  setCentralWidget(simulationSettingsWidget);

  createActions();
  createMenus();
  createToolBars();

  createMainSimulator();
}


MainWindow::~MainWindow()
{
  std::cout << "~MainWindow() - START" << std::endl;

  closeSimulator();

  std::cout << "~MainWindow() - END" << std::endl;
}


void
MainWindow::createMainSimulator()
{
  assert(!m_mainSimulator);
  m_mainSimulator = new MainSimulator(m_simulatorController);
  m_simulatorThread.reset(new std::thread(&MainSimulator::run, m_mainSimulator));
}


void
MainWindow::closeSimulator()
{
  m_simulatorController->setClose(true);

  if (m_simulatorThread->joinable())
  {
    m_simulatorThread->join();
  }

  if (m_mainSimulator)
  {
    delete m_mainSimulator;
    m_mainSimulator = 0;
  }
}


void
MainWindow::createActions()
{
  m_clearAct = new QAction(QIcon("./data/icons/edit-clear.png"), tr("&Clear"), this);
  connect(m_clearAct, SIGNAL(triggered()), this, SLOT(slotClearSimulator()));

  m_playAct = new QAction(QIcon("./data/icons/media-playback-pause.png"), "&Play", this);
  connect(m_playAct, SIGNAL(triggered()), this, SLOT(slotTogglePlay()));

  m_closeAct = new QAction(QIcon("./data/icons/process-stop.png"), "&Close", this);
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
  closeSimulator();
}


void
MainWindow::slotTogglePlay()
{
  m_simulatorController->togglePlay();
  if (m_simulatorController->getPlay())
  {
    m_playAct->setIcon(QIcon("./data/icons/media-playback-pause.png"));
  }
  else
  {
    m_playAct->setIcon(QIcon("./data/icons/media-playback-start.png"));
  }
}


void
MainWindow::slotClearSimulator()
{
  m_simulatorController->setClear(true);
}
