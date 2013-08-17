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

}


SimulationSettingsWidget::~SimulationSettingsWidget()
{
  delete ui;
}


void
SimulationSettingsWidget::slotStepsizeSliderChanged(int stepsizeInteger)
{
  std::cout << "slotStepsizeSliderChanged()" << std::endl;
  double stepsize = stepsizeInteger / 100.0;
  m_controller->setStepSize(stepsize);
  ui->stepsizeSpinBox->setValue(stepsize);
}


void
SimulationSettingsWidget::slotStepsizeSpinBoxChanged(double stepsize)
{
  std::cout << "slotStepsizeSpinBoxChanged()" << std::endl;
  int stepsizeInteger = stepsize * 100.0;
  ui->stepsizeSlider->setValue(stepsizeInteger);
}
