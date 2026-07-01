#include "Controller.h"

#include <cmath>

double Controller::calculateHeading(Point current, Point target) {

  double dx = target.x - current.x;

  double dy = target.y - current.y;

  double angle = atan2(dy, dx);

  return angle * 180.0 / M_PI;
}