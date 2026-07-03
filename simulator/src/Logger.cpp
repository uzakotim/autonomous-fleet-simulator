#include "Logger.h"

#include <fstream>
#include <iostream>

void Logger::log(const VehicleState &state) {
  std::ofstream jsonFile("telemetry.jsonl", std::ios::app);
  jsonFile << "{"
           << "\"vehicle_id\":" << state.id << ","
           << "\"lat\":" << state.lat << ","
           << "\"lon\":" << state.lon << ","
           << "\"speed\":" << state.speed << ","
           << "\"current_node\":" << state.currentNode << ","
           << "\"remaining_waypoints\":" << state.remainingWaypoints
           << "}\n";

  std::ofstream csvFile("telemetry.csv", std::ios::app);
  if (!headerWritten) {
    csvFile << "id,lat,lon,speed,status,current_node,remaining_waypoints\n";
    headerWritten = true;
  }
  csvFile << state.id << "," << state.lat << "," << state.lon << ","
          << state.speed << "," << state.status << "," << state.currentNode
          << "," << state.remainingWaypoints << "\n";
}
