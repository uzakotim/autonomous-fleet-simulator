#pragma once

#include "Point.h"
#include "Sensor.h"

struct VehicleState {
  int id;
  Point position;

  double speed;

  double heading;
};