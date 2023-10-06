#include "include/network.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>
#include <stdexcept>
#include <unistd.h>

Server::Server(int port) : port(port) {
  sockaddr_in server_addr;
  int opt = 1;

  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd == -1) {
    auto error = std::string("ERROR opening socket: ") + std::strerror(errno);
    throw std::runtime_error(error);
  }

  if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt))) {
    auto error = std::string("setsockopt: ") + std::strerror(errno);
    throw std::runtime_error(error);
  }

  bzero((char *)&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(port);

  if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr))) {
    auto error = std::string("ERROR binding socket: ") + std::strerror(errno);
    throw std::runtime_error(error);
  }

  if (listen(socket_fd, queue_size)) {
    auto error = std::string("ERROR listening: ") + std::strerror(errno);
    throw std::runtime_error(error);
  }
}

Server::~Server() { shutdown(); }

int Server::accept() {
  int client_fd = -1;
  sockaddr_in client_addr{};
  socklen_t addrlen = sizeof(client_addr);

  client_fd = ::accept(socket_fd, (sockaddr *)&client_addr, &addrlen);
  if (client_fd < 0) {
    auto error = std::string("ERROR on accept: ") + std::strerror(errno);
    throw std::runtime_error(error);
  }

  Client client(client_fd, inet_ntoa(client_addr.sin_addr),
                ntohs(client_addr.sin_port));
  clients.insert({client_fd, std::move(client)});
  return client_fd;
}

bool Server::isRunning() { return socket_fd != -1; }

void Server::shutdown() {
  if (socket_fd != -1)
    close(socket_fd);
}

bool Server::hasClient(int client_fd) {
  return clients.find(client_fd) != clients.end();
}

Client &Server::getClient(int client_fd) {
  if (!hasClient(client_fd))
    throw std::runtime_error("Client not found");
  return clients.find(client_fd)->second;
}

unsigned int Server::getCount() { return clients.size(); }

Client &Server::operator[](int client_fd) { return getClient(client_fd); }
