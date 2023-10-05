#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <cstdint>
#include <map>
#include <string>

class Client {
  int socket_fd = -1;
  std::string address = "";
  uint16_t port = 0;

public:
  Client() = delete;
  Client(int socket_fd, std::string address, uint16_t port);
  ~Client();

  Client(const Client &) = delete;
  Client &operator=(const Client &) = delete;

  Client(Client &&);
  Client &operator=(Client &&);

  std::string getAddress();
  uint16_t getPort();

  void send(const std::string &msg);
  std::string recv();

  bool isConnected();
  void disconnect();
};

class Server {
  int socket_fd = -1;
  int port;
  int queue_size = 5;
  std::map<int, Client> clients;

public:
  Server(int port);
  ~Server();

  int accept();

  bool hasClient(int client_fd);
  Client &getClient(int client_fd);
  unsigned int getCount();

  bool isRunning();
  void shutdown();

  Client &operator[](int client_fd);
};

#endif // __SERVER_HPP__
