#include "Logger.h"

#include <fstream>
#include <iostream>

void Logger::log(VehicleState state) {

  std::ofstream file;

  file.open("telemetry.csv", std::ios::app);

  file << state.id << "," << state.position.x << "," << state.position.y << ","
       << state.speed << "," << state.status << "\n";

  file.close();
}