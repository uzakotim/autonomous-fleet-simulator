#pragma once

#include "Point.h"
#include "Sensor.h"
#include <string>

struct VehicleState {
  int id;

  Point position;

  double speed;

  double heading;

  std::string status;
};