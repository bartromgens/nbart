#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QPlainTextEdit>

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
  void closeSimulator();

private slots:
  void slotTogglePlay();
  void slotClearSimulator();
  void slotCloseSimulator();

private:
  MainSimulator* m_mainSimulator;
  std::unique_ptr<std::thread> m_simulatorThread;
  std::shared_ptr<SimulatorController> m_simulatorController;

  QMenu* m_fileMenu;
  QToolBar* m_fileToolBar;

  QPlainTextEdit* m_textEdit;

  QAction* m_clearAct;
  QAction* m_playAct;
  QAction* m_closeAct;

};

#endif // MAINWINDOW_H
