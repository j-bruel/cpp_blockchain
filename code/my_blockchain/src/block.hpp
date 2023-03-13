#pragma once

#include <ctime>
#include <string>

namespace centor
{

  class block final
  {
  public:
    explicit block(std::uint32_t index, const std::string &data) noexcept;

    // @param difficulty Leading zeros (or prefix zeros) of the hash determining the difficulty of mining this new block.
    void self_mine_hash_block(unsigned int difficulty) noexcept;
    std::string get_hash() const noexcept;

  private:
    std::string compute_hash() const noexcept;

    std::uint32_t index;
    std::uint32_t nonce{0};// number used once
    std::string data;
    std::string hash;
    std::string parent_hash;
    std::time_t time{std::time(nullptr)};
  };

}