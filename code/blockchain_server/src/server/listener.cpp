#include "listener.hpp"

#include <nlohmann/json.hpp>

namespace srv
{

  listener::listener(const centor::blockchain &blockchain, const std::string &listening_addr, int listening_port) :
    addr(listening_addr), port(listening_port), http_server()
  {
    setup_endpoint(blockchain);
  }

  void listener::listen()
  {
    http_server.listen(addr, port);
  }

  void listener::setup_endpoint(const centor::blockchain &blockchain)
  {
    http_server.Get("/blockchain",
                    [&blockchain](const auto &, httplib::Response &res)
                    { res.set_content(nlohmann::json(blockchain).dump(), "application/json"); });
  }

}