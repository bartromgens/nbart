#include "simulationsettingswidget.h"
#include "ui_simulationsettingswidget.h"

#include "simulatorcontroller.h"

#include <iostream>

SimulationSettingsWidget::SimulationSettingsWidget(std::shared_ptr<SimulatorController> controller, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::SimulationSettingsWidget),
  m_controller(controller)
{
  ui->setupUi(this);

  connect(ui->stepsizeSlider, SIGNAL(valueChanged(int)), this, SLOT(slotStepsizeSliderChanged(int)));
  connect(ui->stepsizeSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slotStepsizeSpinBoxChanged(double)));

  connect(ui->speedSlider, SIGNAL(valueChanged(int)), this, SLOT(slotSpeedSliderChanged(int)));
  connect(ui->speedSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slotSpeedSpinBoxChanged(double)));

  ui->speedSpinBox->setValue(m_controller->getSimulationSpeed());
  ui->stepsizeSpinBox->setValue(m_controller->getStepSize());
}


SimulationSettingsWidget::~SimulationSettingsWidget()
{
  delete ui;
}


void
SimulationSettingsWidget::slotStepsizeSliderChanged(int stepsizeInteger)
{
  double stepsize = stepsizeInteger / 100.0;
  m_controller->setStepSize(stepsize);
  ui->stepsizeSpinBox->setValue(stepsize);
}


void
SimulationSettingsWidget::slotStepsizeSpinBoxChanged(double stepsize)
{
  int stepsizeInteger = stepsize * 100.0;
  ui->stepsizeSlider->setValue(stepsizeInteger);
}


void
SimulationSettingsWidget::slotSpeedSliderChanged(int speedInteger)
{
  double speed = static_cast<double>(speedInteger);
  m_controller->setSimulationSpeed(speed);
  ui->speedSpinBox->setValue(speed);
}


void
SimulationSettingsWidget::slotSpeedSpinBoxChanged(double speed)
{
  int speedInteger = static_cast<double>(speed);
  ui->speedSlider->setValue(speedInteger);
}
