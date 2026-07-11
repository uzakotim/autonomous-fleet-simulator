#include "UdpCommandListener.h"

#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

UdpCommandListener::UdpCommandListener(int port, CommandHandler handler)
    : port_(port), socket_(-1), running_(false), handler_(std::move(handler)) {}

UdpCommandListener::~UdpCommandListener() { stop(); }

void UdpCommandListener::start() {
  running_ = true;
  worker_ = std::thread(&UdpCommandListener::listen, this);
  std::cout << "Listening for commands on port " << port_ << std::endl;
}

void UdpCommandListener::stop() {
  running_ = false;

  if (socket_ >= 0)
    close(socket_);

  if (worker_.joinable())
    worker_.join();
}

void UdpCommandListener::listen() {
  socket_ = socket(AF_INET, SOCK_DGRAM, 0);

  sockaddr_in addr{};

  addr.sin_family = AF_INET;
  addr.sin_port = htons(port_);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  bind(socket_, (sockaddr *)&addr, sizeof(addr));

  char buffer[4096];

  while (running_) {
    sockaddr_in sender{};
    socklen_t len = sizeof(sender);

    int received = recvfrom(socket_, buffer, sizeof(buffer) - 1, 0,
                            (sockaddr *)&sender, &len);

    if (received <= 0)
      continue;

    buffer[received] = '\0';

    handler_(buffer);
  }
}