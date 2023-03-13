#pragma once

#include "block.hpp"

#include <optional>
#include <vector>

namespace centor
{

  class blockchain final
  {
  public:
    blockchain() noexcept;

    void add_block(std::uint32_t block_index, const std::string &block_data);

  private:
    std::optional<block> get_last_block() const noexcept;

    std::uint32_t difficulty;
    std::vector<block> chain;
  };

}