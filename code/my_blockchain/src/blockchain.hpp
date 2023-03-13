#pragma once

#include "block.hpp"

#include <optional>
#include <vector>

namespace centor
{

  class blockchain final
  {
  public:
    blockchain();

    void add_block(const block &new_block);

  private:
    std::optional<block> get_last_block() const;

    unsigned int difficulty;
    std::vector<block> chain;
  };

}