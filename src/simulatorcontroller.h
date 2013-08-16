#ifndef SIMULATORCONTROLLER_H
#define SIMULATORCONTROLLER_H

#include <atomic>

class SimulatorController
{
public:
  SimulatorController();
  ~SimulatorController();

  bool getClose() const;
  void setClose(bool close);

  bool getClear() const;
  void setClear(bool clear);

  bool getPlay() const;
  void togglePlay();

  bool getShowTrajectories() const;
  void setShowTrajectories(bool showTrajectories);
  void toggleShowTrajectories();

  bool getShowField() const;
  void setShowField(bool showField);
  void toggleShowField();

  double getSimulationSpeed() const;
  void setSimulationSpeed(double simulationSpeed);
  void increaseSimulationSpeed();
  void decreaseSimulationSpeed();

  bool getShowBodies() const;
  void setShowBodies(bool showBodies);
  void toggleShowBodies();

private:
  std::atomic<bool> m_close;
  std::atomic<bool> m_clear;
  std::atomic<bool> m_play;
  std::atomic<bool> m_showBodies;
  std::atomic<bool> m_showTrajectories;
  std::atomic<bool> m_showField;
  std::atomic<double> m_simulationSpeed;
};

#endif // SIMULATORCONTROLLER_H
