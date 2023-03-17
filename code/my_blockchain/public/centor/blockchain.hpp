#pragma once

#include "block.hpp"
#include "my_blockchain_export.hpp"

#include <nlohmann/json.hpp>
#include <optional>
#include <vector>
#include <mutex>

namespace centor
{

  class MY_BLOCKCHAIN_EXPORT blockchain final
  {
  public:
    blockchain() noexcept;

    void to_json(nlohmann::json &json) const;

    void add_block(std::uint32_t block_index, const std::string &block_data);
    [[nodiscard]] std::optional<block> get_parent_block(const block &child_block) const noexcept;
    [[nodiscard]] std::optional<block> get_last_block() const noexcept;
    [[nodiscard]] std::optional<block> get_block_by_hash(const std::string &hash) const noexcept;

  private:
    std::mutex mtx;
    std::uint32_t difficulty;
    std::vector<block> chain;
  };

  MY_BLOCKCHAIN_EXPORT void to_json(nlohmann::json &json, const blockchain &to_serialize);

}