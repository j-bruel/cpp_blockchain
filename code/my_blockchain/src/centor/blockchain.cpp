#include "centor/blockchain.hpp"

#include "centor/blockchain_handling_exception.hpp"

#include <iostream>
#include <spdlog/spdlog.h>

namespace centor
{

  static constexpr auto leading_zeros = 4;

  blockchain::blockchain() noexcept : difficulty(leading_zeros)
  {
    chain.emplace_back(0, "Genesis Block");
  }

  void blockchain::to_json(nlohmann::json &json) const
  {
    json = chain;
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
    spdlog::info("Block added to the chain {}!", new_block.get_hash());
  }

  std::optional<block> blockchain::get_last_block() const noexcept
  {
    if (chain.empty())
      return std::nullopt;
    return chain.back();
  }

  std::optional<block> blockchain::get_parent_block(const block &child_block) const noexcept
  {
    if (chain.empty())
      return std::nullopt;
    return get_block_by_hash(child_block.get_parent_hash());
  }

  std::optional<block> blockchain::get_block_by_hash(const std::string &hash) const noexcept
  {
    const auto search_result =
      std::ranges::find_if(chain, [&hash](const auto &block_in_chain) { return hash == block_in_chain.get_hash(); });

    if (search_result == chain.end())
      return std::nullopt;
    return *search_result;
  }

  void to_json(nlohmann::json &json, const blockchain &to_serialize)
  {
    to_serialize.to_json(json);
  }

}