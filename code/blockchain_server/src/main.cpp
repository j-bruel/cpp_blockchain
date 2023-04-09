#include "server/listener.hpp"

#include <centor/blockchain.hpp>
#include <centor/blockchain_handling_exception.hpp>
#include <cpplog/log.hpp>
#include <thread>

static void mining_main(centor::blockchain &blockchain)
{
  cpplog::info("Mining while is starting.");
  try
  {
    for (std::uint32_t block_number = 1; true; ++block_number)
      blockchain.add_block(block_number, fmt::format("Block number {}.", block_number));
  }
  catch (const centor::blockchain_handling_exception &e)
  {
    cpplog::critical("Mining is stopped, reason: ", e.what());
  }
}

int main()
{
  constexpr auto server_addr = "0.0.0.0";
  constexpr auto server_port = 8000;
  centor::blockchain blockchain;
  srv::listener http_server_listener(blockchain, server_addr, server_port);
  std::thread mining_thread(&mining_main, std::ref(blockchain));

  cpplog::info("Running HTTP server");
  http_server_listener.listen();
  mining_thread.join();
  return EXIT_SUCCESS;
}
