#include "Vehicle.h"
#include "Controller.h"
#include "State.h"
#include <cmath>

Vehicle::Vehicle(int id) {

  state.id = id;

  state.position.x = 0;
  state.position.y = 0;

  state.speed = 5;

  state.heading = 0;

  destination.x = 100;
  destination.y = 100;
}

void Vehicle::update(double dt) {

  Controller controller;

  state.heading = controller.calculateHeading(state.position, destination);

  double radians = state.heading * M_PI / 180;

  state.position.x += cos(radians) * state.speed * dt;

  state.position.y += sin(radians) * state.speed * dt;
}

VehicleState Vehicle::getState() { return state; }