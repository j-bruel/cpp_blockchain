#pragma once

#include <centor/blockchain.hpp>

#include <string>
#include <httplib.h>

namespace srv
{

  class listener final
  {
  public:
    listener() = delete;
    explicit listener(const centor::blockchain &blockchain, const std::string &listening_addr, int listening_port);

    void listen();

  private:
    void setup_endpoint(const centor::blockchain &blockchain);

    std::string addr;
    int port;
    httplib::Server http_server;
  };

}