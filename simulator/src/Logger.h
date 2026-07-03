#pragma once

#include "State.h"

class Logger {

public:
  void log(const VehicleState &state);

private:
  bool headerWritten = false;
};
