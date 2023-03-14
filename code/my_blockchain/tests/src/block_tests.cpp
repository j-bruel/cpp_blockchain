#include "block.hpp"

#include <gtest/gtest.h>

namespace centor
{

  TEST(BlockTest, BlockHasCorrectData)
  {
    block b(1, "block data");

    EXPECT_EQ(b.get_data(), "block data");// check that the block has the correct data
  }

  TEST(BlockTest, HashIsComputedCorrectly)
  {
    block b(0, "test data");

    {
      b.self_mine_hash_block(1);
      EXPECT_EQ(b.get_hash().substr(0, 1), "0");
    }
    {
      b.self_mine_hash_block(2);
      EXPECT_EQ(b.get_hash().substr(0, 2), "00");
    }
    {
      b.self_mine_hash_block(3);
      EXPECT_EQ(b.get_hash().substr(0, 3), "000");
    }
    {
      b.self_mine_hash_block(4);
      EXPECT_EQ(b.get_hash().substr(0, 4), "0000");// check that the hash has 4 leading zeros
    }
  }

  TEST(BlockTest, ParentHashIsLinked)
  {
    block parent(0, "parent data");
    block child(1, "child data");

    child.link_parent_block(parent);
    EXPECT_EQ(child.get_parent_hash(), parent.get_hash());// check that the parent hash is linked correctly
  }

  TEST(BlockTest, SameDataProducesDifferentHashes)
  {
    block b1(0, "test data #1");
    block b2(0, "test data #2");

    b1.self_mine_hash_block(2);
    b2.self_mine_hash_block(2);
    EXPECT_NE(b1.get_hash(), b2.get_hash());// check that the same data produces different hashes with different nonces
  }

  TEST(BlockTest, BlockHasCorrectHashWithParent)
  {
    block parent_block(1, "parent block data");
    block child_block(2, "child block data");

    parent_block.self_mine_hash_block(4);// mine the parent block with a difficulty of 4 leading zeros
    child_block.link_parent_block(parent_block);
    child_block.self_mine_hash_block(4);// mine the child block with a difficulty of 4 leading zeros
    EXPECT_EQ(child_block.get_hash().substr(0, 4),
              "0000");// check that the child block has the correct hash (4 leading zeros)
  }

  TEST(BlockTest, BlockHasDifferentHashWithDifferentNonce)
  {
    block b(1, "block data");

    b.self_mine_hash_block(4);// mine the block with a difficulty of 4 leading zeros

    const auto first_hash = b.get_hash();

    b.self_mine_hash_block(4);// mine the block again with a different nonce

    const auto second_hash = b.get_hash();

    EXPECT_NE(first_hash, second_hash);// check that the block has a different hash with a different nonce
  }

}