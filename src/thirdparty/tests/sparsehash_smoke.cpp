/*
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Copyright (c) 2017-2018, Lawrence Livermore National Security, LLC.
 *
 * Produced at the Lawrence Livermore National Laboratory
 *
 * LLNL-CODE-741217
 *
 * All rights reserved.
 *
 * This file is part of Axom.
 *
 * For details about use and distribution, please read axom/LICENSE.
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

//-----------------------------------------------------------------------------
///
/// file: sparsehash_smoke.cpp
/// A simple test to see if the sparsehash libary is working properly.
///
//-----------------------------------------------------------------------------

#include "sparsehash/dense_hash_map"

#include "gtest/gtest.h"

//-----------------------------------------------------------------------------
TEST(sparsehash_smoke, basic_use)
{
  typedef google::dense_hash_map<std::string, double> MapType;

  const std::string deletedKey = "DELETED";
  const std::string emptyKey   = "EMPTY";

  MapType map;
  map.set_empty_key(emptyKey);     // always need to set this for dense_hash_map
  map.set_deleted_key(deletedKey); // need to set this to enable erasing

  EXPECT_EQ( 0, map.size());

  map["penny"]   = 0.01;
  map["nickel"]  = 0.05;
  map["dime"]    = 0.10;
  map["quarter"] = 0.25;

  EXPECT_EQ( 4, map.size());

  EXPECT_EQ( 0.25, map["quarter"] );
  EXPECT_TRUE( map.find("no-coin") == map.end() );

  map.erase("penny");
  EXPECT_TRUE( map.find("penny") == map.end() );
}