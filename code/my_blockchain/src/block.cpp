#include "block.hpp"

#include <array>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <cstddef>
#include <fmt/format.h>
#include <span>
#include <string>

namespace centor
{

  block::block(std::uint32_t index, const std::string &data) noexcept : index(index), data(data) { }

  void block::self_mine_hash_block(std::uint32_t difficulty) noexcept
  {
    std::string hash_leading_zeros(difficulty, '0');
    std::string tmp_hash;

    while (tmp_hash.substr(0, difficulty) != hash_leading_zeros)
    {
      ++nonce;
      tmp_hash = compute_hash();
    }
    hash = tmp_hash;
    std::cout << "New block mined : " << hash << std::endl;
  }

  std::string block::get_hash() const noexcept
  {
    return hash;
  }

  void block::link_parent_block(const block &parent_block) noexcept
  {
    parent_hash = parent_block.hash;
  }

  static const std::string &
  convert_hash_to_hex_string(std::string &hash, const std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE> &digest)
  {
    CryptoPP::HexEncoder hex_encoder(new CryptoPP::StringSink(hash));

    hex_encoder.Put(digest.data(), digest.size());
    hex_encoder.MessageEnd();
    return hash;
  }

  std::string block::compute_hash() const noexcept
  {
    std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE> digest{};
    const auto clear_hash = generate_clear_hash();
    std::string computed_hash;

    CryptoPP::SHA256().CalculateDigest(digest.data(), reinterpret_cast<const CryptoPP::byte *>(clear_hash.data()),
                                       clear_hash.length());
    computed_hash = convert_hash_to_hex_string(computed_hash, digest);
//    std::cout << "clear: " << clear_hash << std::endl;
    //    std::cout << "hash: " << computed_hash << std::endl;
    return computed_hash;
  }

  std::string block::generate_clear_hash() const noexcept
  {
    return fmt::format("{}{}{}{}{}", index, time, data, nonce, parent_hash);
  }

}