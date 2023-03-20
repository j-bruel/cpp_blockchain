#include "listener.hpp"

#include <nlohmann/json.hpp>

namespace srv
{

  listener::listener(const centor::blockchain &blockchain, std::string listening_addr, int listening_port) :
    addr(std::move(listening_addr)), port(listening_port)
  {
    setup_endpoint(blockchain);
  }

  void listener::listen()
  {
    http_server.listen(addr, port);
  }

  void listener::setup_endpoint(const centor::blockchain &blockchain)
  {
    constexpr auto beautify_json_dump = 4;

    http_server.Get("/blockchain",
                    [&blockchain](const auto &, httplib::Response &res)
                    { res.set_content(nlohmann::json(blockchain).dump(beautify_json_dump), "application/json"); });
  }

}
