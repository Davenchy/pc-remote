#include "include/network.hpp"
#include <iostream>

void error(const char *msg) {
  perror(msg);
  exit(1);
}

int main() {
  Server server(1234);

  int client = server.accept();
  if (client == -1)
    return 1;

  Client &client1 = server.getClient(client);
  std::cout << "Connected: " << client1.getAddress() << ":" << client1.getPort()
            << std::endl;
  client1.send("hello");

  std::string msg = client1.recv();
  printf("msg: %s\n", msg.c_str());

  client1.disconnect();
  server.shutdown();
  return 0;
}
