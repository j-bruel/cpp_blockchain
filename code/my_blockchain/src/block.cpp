#include "block.hpp"

#include <fmt/format.h>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>

#include <string>
#include <cstddef>

namespace centor
{

  block::block(std::uint32_t index, const std::string &data) noexcept : index(index), data(data) { }

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
    std::string clear_hash = fmt::format("{}{}{}{}{}", index, time, data, nonce, parent_hash);
    std::string hash_str;
    CryptoPP::SHA256 hasher;

    CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];
    hasher.CalculateDigest(digest, (const CryptoPP::byte *)clear_hash.c_str(), clear_hash.length());

    // Convert the hash to a hex string
    CryptoPP::HexEncoder encoder;

    encoder.Attach(new CryptoPP::StringSink(hash_str));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();
    std::cout << "clear: " << clear_hash << std::endl;
    std::cout << "hash: " << hash_str << std::endl;
    return hash_str;
  }


}