#pragma once
#include "Point.h"
#include "Sensor.h"
#include "State.h"

class Vehicle {

public:
  Vehicle(int id);
  Sensor sensor;
  void update(double dt);

  VehicleState getState();
  void setDestination(Point target);
  void setInitialPosition(Point position);
  void stop();

private:
  VehicleState state;
  Point destination;
  bool emergencyStop;
};