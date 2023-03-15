#include "centor/blockchain.hpp"

#include <gtest/gtest.h>

namespace centor
{

  static constexpr auto block_data_1 = "block 1 data";
  static constexpr auto block_data_2 = "block 2 data";

  TEST(BlockchainTest, GenesisBlockIsAddedOnConstruction)
  {
    const blockchain simple_blockchain;
    const auto last_block = simple_blockchain.get_last_block();

    if (!last_block)
      FAIL() << "Last block not found.";
    EXPECT_EQ(last_block->get_data(),
              "Genesis Block");// check that the genesis block is added on construction
  }

  TEST(BlockchainTest, BlocksAreAddedSequentially)
  {
    blockchain simple_blockchain;

    simple_blockchain.add_block(1, block_data_1);
    simple_blockchain.add_block(2, block_data_2);

    const auto last_block = simple_blockchain.get_last_block();

    if (!last_block)
      FAIL() << "Last block not found.";
    EXPECT_EQ(last_block->get_data(),
              block_data_2);// check that blocks are added sequentially
  }

  TEST(BlockchainTest, GetParentBlockReturnsParentBlock)
  {
    blockchain simple_blockchain;

    simple_blockchain.add_block(1, block_data_1);
    simple_blockchain.add_block(2, block_data_2);

    const auto last_block = simple_blockchain.get_last_block();
    const auto parent_block = simple_blockchain.get_parent_block(*last_block);

    if (!last_block)
      FAIL() << "Last block not found.";
    if (!parent_block)
      FAIL() << "Parent block not found.";
    EXPECT_EQ(parent_block->get_data(), block_data_1);// check that get_parent_block() returns the parent block
  }

  TEST(BlockchainTest, GetBlockByHashReturnsBlock)
  {
    blockchain simple_blockchain;

    simple_blockchain.add_block(1, block_data_1);

    const auto last_block = simple_blockchain.get_last_block();

    if (!last_block)
      FAIL() << "Last block not found.";

    const auto searched_block = simple_blockchain.get_block_by_hash(last_block->get_hash());

    if (!searched_block)
      FAIL() << "Searched block (== last block) not found.";
    EXPECT_EQ(searched_block->get_data(), last_block->get_data());
    EXPECT_EQ(searched_block->get_data(), block_data_1);// check that get_block_by_hash() returns the correct block
  }

  TEST(BlockchainTest, GetBlockByHashReturnsNullOptionalWhenNotFound)
  {
    const blockchain simple_blockchain;
    const auto searched_block = simple_blockchain.get_block_by_hash("nonexistent hash");

    EXPECT_FALSE(
      searched_block.has_value());// check that get_block_by_hash() returns a null optional when the block is not found
  }

}