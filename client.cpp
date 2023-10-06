#include "include/network.hpp"
#include <cstring>
#include <stdexcept>
#include <string>
#include <unistd.h>

Client::Client(int socket_fd, std::string address, uint16_t port)
    : socket_fd(socket_fd), address(address), port(port) {}

Client::~Client() { disconnect(); }

Client::Client(Client &&other) {
  // copy other object data
  socket_fd = other.socket_fd;
  port = other.port;
  address = other.address;
  // delete other object data
  other.socket_fd = -1;
  other.port = 0;
  other.address.clear();
}

Client &Client::operator=(Client &&other) {
  // copy other object data
  socket_fd = other.socket_fd;
  port = other.port;
  address = other.address;
  // delete other object data
  other.socket_fd = -1;
  other.port = 0;
  other.address.clear();
  return *this;
}

std::string Client::getAddress() { return address; }
uint16_t Client::getPort() { return port; }

void Client::send(const std::string &msg) {
  ssize_t size = -1;

  size = write(socket_fd, msg.c_str(), msg.size());
  if (size == -1) {
    auto error =
        std::string("ERROR writing to socket: ") + std::strerror(errno);
    throw std::runtime_error(error);
  }
}

std::string Client::recv() {
  char buf[1024];
  ssize_t size = -1;

  size = read(socket_fd, buf, 1024);
  if (size == -1) {
    auto error =
        std::string("ERROR reading from socket: ") + std::strerror(errno);
    throw std::runtime_error(error);
  }

  return std::string(buf, size);
}

bool Client::isConnected() { return socket_fd != -1; }

void Client::disconnect() {
  if (socket_fd != 0)
    close(socket_fd);
}

uint16_t Server::getPort() { return port; }
