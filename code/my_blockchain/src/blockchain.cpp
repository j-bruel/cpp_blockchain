#include "blockchain.hpp"
#include "blockchain_handling_exception.hpp"

#include <iostream>

namespace centor
{

  static constexpr auto leading_zeros = 3;

  blockchain::blockchain() noexcept : difficulty(leading_zeros)
  {
    chain.emplace_back(block(0, "Genesis Block"));
  }

  void blockchain::add_block(std::uint32_t block_index, const std::string &block_data)
  {
    const auto last_block = get_last_block();
    auto new_block = block(block_index, block_data);

    if (!last_block)
      throw blockchain_handling_exception("No genesis block, impossible to add a block.");
    new_block.link_parent_block(*last_block);
    new_block.self_mine_hash_block(difficulty);
    chain.push_back(new_block);
    std::cout << "Block added to the chain : " << new_block.get_hash() << std::endl;
  }

  std::optional<block> blockchain::get_last_block() const noexcept
  {
    if (chain.empty())
      return std::nullopt;
    return chain.back();
  }

}