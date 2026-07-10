#include "UdpClient.h"

#include <arpa/inet.h>
#include <unistd.h>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

UdpClient::UdpClient(const std::string &host, int port) {
  socketFd = socket(AF_INET, SOCK_DGRAM, 0);

  serverAddr.sin_family = AF_INET;

  serverAddr.sin_port = htons(port);

  inet_pton(AF_INET, host.c_str(), &serverAddr.sin_addr);
}

UdpClient::~UdpClient() { close(socketFd); }

bool UdpClient::sendTelemetry(const VehicleState &state) {
  json packet = {

      {"vehicle_id", state.id},

      {"latitude", state.lat},

      {"longitude", state.lon},

      {"speed", state.speed},

      {"heading", state.heading},

      {"status", state.status},

      {"battery", state.battery}

  };

  std::string payload = packet.dump();

  sendto(socketFd,

         payload.c_str(),

         payload.size(),

         0,

         (sockaddr *)&serverAddr,

         sizeof(serverAddr));

  return true;
}