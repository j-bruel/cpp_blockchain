#include "listener.hpp"

namespace srv
{

  listener::listener(const std::string &listening_addr, int listening_port) :
    addr(listening_addr), port(listening_port), http_server()
  {
    setup_endpoint();
  }

  void listener::listen()
  {
    http_server.listen(addr, port);
  }

  void listener::setup_endpoint()
  {
    http_server.Get("/test",
                    [](const httplib::Request &req, httplib::Response &res)
                    { res.set_content("Hello World!", "text/plain"); });
  }

}