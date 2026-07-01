#include "Sensor.h"
#include "State.h"

class Vehicle {

public:
  Vehicle(int id);

  void update(double dt);
  Sensor sensor;

  VehicleState getState();

  void setDestination(Point target);

private:
  VehicleState state;

  Point destination;
};