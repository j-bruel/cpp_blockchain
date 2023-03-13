#include "blockchain.hpp"

#include <chrono>
#include <fmt/format.h>
#include <future>
#include <iostream>

int main(int argc, const char * const *argv)
{
  centor::blockchain blockchain;
  int block_number = 1;

  while (true)
  {
    auto add_block = std::async(std::launch::async,
                                [&blockchain, &block_number]()
                                { blockchain.add_block(block_number, fmt::format("Block number {}.", block_number)); });
    add_block.wait();
    ++block_number;
  }
  return EXIT_SUCCESS;
}