#pragma once

#include "my_blockchain_export.hpp"

#include <ctime>
#include <string>

namespace centor
{

  class MY_BLOCKCHAIN_EXPORT block final
  {
  public:
    explicit block(std::uint32_t index, const std::string &block_data) noexcept;

    // @param difficulty Leading zeros (or prefix zeros) of the hash determining the difficulty of mining this new block.
    void self_mine_hash_block(std::uint32_t difficulty) noexcept;
    void link_parent_block(const block &parent_block) noexcept;
    [[nodiscard]] std::string get_data() const noexcept;
    [[nodiscard]] std::string get_hash() const noexcept;
    [[nodiscard]] std::string get_parent_hash() const noexcept;

  private:
    [[nodiscard]] std::string compute_hash() const noexcept;
    [[nodiscard]] std::string generate_clear_hash() const noexcept;

    std::uint32_t index;
    std::uint32_t nonce{0};// number used once
    std::string data;
    std::string hash;
    std::string parent_hash;
    std::time_t time{std::time(nullptr)};
  };

}