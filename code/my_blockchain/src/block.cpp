#include "block.hpp"

#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <cstddef>
#include <fmt/format.h>
#include <string>

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

  static const std::string &convert_hash_to_hex_string(std::string &hash, const CryptoPP::byte *digest,
                                                       size_t digest_length)
  {
    CryptoPP::HexEncoder hex_encoder;

    hex_encoder.Attach(new CryptoPP::StringSink(hash));
    hex_encoder.Put(digest, digest_length);
    hex_encoder.MessageEnd();
    return hash;
  }

  std::string block::compute_hash() const noexcept
  {
    CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];
    const auto clear_hash = generate_clear_hash();
    std::string computed_hash;

    CryptoPP::SHA256().CalculateDigest(digest, reinterpret_cast<const CryptoPP::byte *>(clear_hash.c_str()),
                                       clear_hash.length());
    computed_hash = convert_hash_to_hex_string(computed_hash, digest, sizeof(digest));
    std::cout << "clear: " << clear_hash << std::endl;
    std::cout << "hash: " << computed_hash << std::endl;
    return computed_hash;
  }

  std::string block::generate_clear_hash() const noexcept
  {
    return fmt::format("{}{}{}{}{}", index, time, data, nonce, parent_hash);
  }


}