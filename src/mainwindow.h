#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QObject>

#include <memory>
#include <thread>

class MainSimulator;
class SimulatorController;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:

  explicit MainWindow();
  ~MainWindow();


  void createActions();
  void createToolBars();
  void createMenus();

private:
  void createMainSimulator();

private slots:
  void slotCloseSimulator();

private:

  QPlainTextEdit* m_textEdit;
  QAction* m_newAct;

  QToolBar* m_fileToolBar;
  QMenu* m_fileMenu;

  MainSimulator* m_mainSimulator;
  std::unique_ptr<std::thread> m_simulatorThread;
  std::shared_ptr<SimulatorController> m_simulatorController;
};

#endif // MAINWINDOW_H
