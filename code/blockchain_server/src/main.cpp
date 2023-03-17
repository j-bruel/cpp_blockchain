#include "server/listener.hpp"

#include <centor/blockchain.hpp>
#include <spdlog/spdlog.h>
#include <thread>

static void mining_main(centor::blockchain &blockchain)
{
  spdlog::info("Mining while is starting.");
  for (int block_number = 1; true; ++block_number)
    blockchain.add_block(block_number, fmt::format("Block number {}.", block_number));
}

int main()
{
  centor::blockchain blockchain;
  srv::listener http_server_listener(blockchain, "localhost", 4242);
  std::jthread mining_thread(&mining_main, std::ref(blockchain));

  spdlog::info("Running HTTP server");
  http_server_listener.listen();
  return EXIT_SUCCESS;
}