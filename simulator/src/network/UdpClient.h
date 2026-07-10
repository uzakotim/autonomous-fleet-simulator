#pragma once

#include <string>

#include "../State.h"
#include <arpa/inet.h>

class UdpClient {
public:
  UdpClient(const std::string &host, int port);

  ~UdpClient();

  bool sendTelemetry(const VehicleState &state);

private:
  int socketFd;

  struct sockaddr_in serverAddr;
};