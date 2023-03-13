#include "block.hpp"

#include <string>

namespace centor
{

  block::block(unsigned int index, const std::string &data) noexcept : index(index), data(data) { }

  void block::self_mine_hash_block(unsigned int difficulty) noexcept
  {
    std::string hash_leading_zeros(difficulty, '0');
    std::string tmp_hash;

    while (tmp_hash.substr(0, difficulty) != hash_leading_zeros)
    {
      ++nonce;
      tmp_hash = compute_hash();
    }
    hash = tmp_hash;
  }

  std::string block::get_hash() const noexcept
  {
    return hash;
  }

  std::string block::compute_hash() const noexcept
  {
      // @todo
    return "";
  }


}