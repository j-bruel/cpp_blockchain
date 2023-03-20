#pragma once

#include "my_blockchain_export.hpp"

#include <centor/tools/warning_disabler.hpp>
#include <ctime>
#include <nlohmann/json.hpp>
#include <string>

namespace centor
{

  class MY_BLOCKCHAIN_EXPORT block final
  {
  public:
    explicit block(std::uint32_t index, std::string block_data) noexcept;

    // @param difficulty Leading zeros (or prefix zeros) of the hash determining the difficulty of mining this new block.
    void self_mine_hash_block(std::uint32_t difficulty);
    void link_parent_block(const block &parent_block);
    [[nodiscard]] std::string get_data() const;
    [[nodiscard]] std::string get_hash() const;
    [[nodiscard]] std::string get_parent_hash() const;
    void to_json(nlohmann::json &json) const noexcept;

  private:
    [[nodiscard]] std::string compute_hash() const;
    [[nodiscard]] std::string generate_clear_hash() const noexcept;

    DISABLE_WARNING_PUSH
    DISABLE_WARNING_EXPORTED_DATA_MISMATCH

    std::uint32_t index;
    std::uint32_t nonce{0};// number used once
    std::string data;
    std::string hash;
    std::string parent_hash;
    std::time_t time{std::time(nullptr)};

    DISABLE_WARNING_POP
  };

  MY_BLOCKCHAIN_EXPORT void to_json(nlohmann::json &json, const block &to_serialize) noexcept;

}
