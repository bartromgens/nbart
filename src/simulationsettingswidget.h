#ifndef SIMULATIONSETTINGSWIDGET_H
#define SIMULATIONSETTINGSWIDGET_H

#include <QWidget>

#include <memory>

class SimulatorController;

namespace Ui {
class SimulationSettingsWidget;
}

class SimulationSettingsWidget : public QWidget
{
  Q_OBJECT
  
public:
  explicit SimulationSettingsWidget(std::shared_ptr<SimulatorController> controller, QWidget *parent = 0);
  ~SimulationSettingsWidget();
  
private slots:
  void slotStepsizeSliderChanged(int stepsizeInteger);

  void slotStepsizeSpinBoxChanged(double stepsize);

  void slotSpeedSliderChanged(int speedInteger);
  void slotSpeedSpinBoxChanged(double speed);
private:
  Ui::SimulationSettingsWidget *ui;

  std::shared_ptr<SimulatorController> m_controller;
};

#endif // SIMULATIONSETTINGSWIDGET_H
