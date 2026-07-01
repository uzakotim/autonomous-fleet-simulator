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
  emergencyStop = false;
  state.status = "moving";
}

void Vehicle::update(double dt) {

  Controller controller;

  state.heading = controller.calculateHeading(state.position, destination);

  double radians = state.heading * M_PI / 180;

  if (emergencyStop) {
    state.speed = 0;
    state.status = "stopped";
    return;
  }

  state.position.x += cos(radians) * state.speed * dt;

  state.position.y += sin(radians) * state.speed * dt;
}

void Vehicle::setDestination(Point target) { destination = target; }

void Vehicle::setInitialPosition(Point position) { state.position = position; }

void Vehicle::stop() {
  state.speed = 0;
  state.status = "stopped";
}

VehicleState Vehicle::getState() { return state; }