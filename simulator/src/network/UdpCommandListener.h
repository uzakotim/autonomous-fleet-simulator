#pragma once

#include <atomic>
#include <functional>
#include <thread>

class UdpCommandListener {
public:
  using CommandHandler = std::function<void(const std::string &)>;

  UdpCommandListener(int port, CommandHandler handler);

  ~UdpCommandListener();

  void start();

  void stop();

private:
  void listen();

  int port_;

  int socket_;

  std::atomic<bool> running_;

  std::thread worker_;

  CommandHandler handler_;
};