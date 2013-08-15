#ifndef SIMULATORCONTROLLER_H
#define SIMULATORCONTROLLER_H

#include <atomic>

class SimulatorController
{
public:
  SimulatorController();
  ~SimulatorController();

  bool getClose();
  void setClose(bool close);

  bool getClear() const;
  void setClear(bool clear);

private:
  std::atomic<bool> m_close;
  std::atomic<bool> m_clear;
};

#endif // SIMULATORCONTROLLER_H
