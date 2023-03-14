#include "blockchain.hpp"

#include <gtest/gtest.h>

namespace centor
{

  TEST(BlockchainTest, GenesisBlockIsAddedOnConstruction)
  {
    blockchain b;

    EXPECT_EQ(b.get_last_block()->get_data(), "Genesis Block");// check that the genesis block is added on construction
  }

  TEST(BlockchainTest, BlocksAreAddedSequentially)
  {
    blockchain b;

    b.add_block(1, "block 1 data");
    b.add_block(2, "block 2 data");
    EXPECT_EQ(b.get_last_block()->get_data(), "block 2 data");// check that blocks are added sequentially
  }

  TEST(BlockchainTest, GetParentBlockReturnsParentBlock)
  {
    blockchain b;

    b.add_block(1, "block 1 data");
    b.add_block(2, "block 2 data");

    const auto last_block = b.get_last_block();
    const auto parent_block = b.get_parent_block(*last_block);

    EXPECT_EQ(parent_block->get_data(), "block 1 data");// check that get_parent_block() returns the parent block
  }

  TEST(BlockchainTest, GetBlockByHashReturnsBlock)
  {
    blockchain b;

    b.add_block(1, "block 1 data");

    const auto block = b.get_last_block();
    const auto searched_block = b.get_block_by_hash(block->get_hash());

    EXPECT_EQ(searched_block->get_data(), block->get_data());
    EXPECT_EQ(searched_block->get_data(), "block 1 data");// check that get_block_by_hash() returns the correct block
  }

  TEST(BlockchainTest, GetBlockByHashReturnsNullOptionalWhenNotFound)
  {
    blockchain b;
    const auto searched_block = b.get_block_by_hash("nonexistent hash");

    EXPECT_FALSE(
      searched_block.has_value());// check that get_block_by_hash() returns a null optional when the block is not found
  }

}