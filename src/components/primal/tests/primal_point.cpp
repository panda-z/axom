/*
 * Copyright (c) 2015, Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 *
 * All rights reserved.
 *
 * This source code cannot be distributed without permission and further
 * review from Lawrence Livermore National Laboratory.
 */



#include "gtest/gtest.h"

#include "primal/Point.hpp"

//------------------------------------------------------------------------------
TEST( quest_point, point_default_constructor)
{
  static const int DIM = 2;
  typedef double CoordType;
  typedef primal::Point<CoordType, DIM> QPoint;

  QPoint pt;

  EXPECT_EQ(pt[0], CoordType() );
  EXPECT_EQ(pt.dimension(), DIM );

}


//------------------------------------------------------------------------------
TEST( quest_point, point_singleVal_constructor)
{
  static const int DIM = 5;
  typedef int CoordType;
  typedef primal::Point<CoordType, DIM> QPoint;
  const int singleVal = 10;

  //
  std::cout<<"\nQuest: testing constructor that sets all values to the same singleVal. "
           << "Default second parameter of constructor is DIM."
           << std::endl;
  QPoint pt1( singleVal );

  for(int dim=0; dim<DIM; ++dim)
      EXPECT_EQ(pt1[dim], singleVal );

  //
  std::cout<<"\nQuest: testing constructor that sets all values to the same singleVal. "
           << "Using explicit second parameter set to DIM."
           << std::endl;
  QPoint pt2( singleVal, DIM );

  for(int dim=0; dim<DIM; ++dim)
      EXPECT_EQ(pt2[dim], singleVal );

  //
  std::cout<<"\nQuest: testing constructor that sets all values to the same singleVal. "
           << "Using explicit second parameter set higher than DIM."
           << std::endl;
  QPoint pt3( singleVal, DIM *2 );

  for(int dim=0; dim<DIM; ++dim)
      EXPECT_EQ(pt3[dim], singleVal );


  //
  std::cout<<"\nQuest: testing constructor that sets *some* values to the same singleVal. "
           << "Using explicit second parameter set less than DIM. "
           << "Other values should be set to zero. "
           << std::endl;
  int numVals = DIM / 2;
  QPoint pt4( singleVal, numVals);

  for(int dim=0; dim<numVals; ++dim)
      EXPECT_EQ(pt4[dim], singleVal );

  for(int dim=numVals+1; dim<DIM; ++dim)
      EXPECT_EQ(pt4[dim], CoordType() );

}


//------------------------------------------------------------------------------
TEST( quest_point, point_array_constructor)
{
  static const int DIM = 5;
  typedef int CoordType;
  typedef primal::Point<CoordType, DIM> QPoint;

  // Set elt i of input array to i
  CoordType arr[DIM];
  for(int dim=0; dim<DIM; ++dim)
      arr[dim] = dim;

  //
  std::cout<<"\nQuest: testing constructor that copies entire array. "
           << "Default second parameter of constructor is DIM."
           << std::endl;
  QPoint pt1( arr );

  for(int dim=0; dim<DIM; ++dim)
      EXPECT_EQ(pt1[dim], arr[dim]);

  //
  std::cout<<"\nQuest: testing constructor that copies entire array. "
           << "Using explicit second parameter set to DIM."
           << std::endl;
  QPoint pt2( arr, DIM );

  for(int dim=0; dim<DIM; ++dim)
      EXPECT_EQ(pt2[dim], arr[dim]);

  //
  std::cout<<"\nQuest: testing constructor that copies entire array. "
           << "Using explicit second parameter set higher than DIM."
           << std::endl;
  QPoint pt3( arr, DIM *2 );

  for(int dim=0; dim<DIM; ++dim)
      EXPECT_EQ(pt3[dim], arr[dim]);


  //
  std::cout<<"\nQuest: testing constructor that sets *some* values to the same singleVal. "
           << "Using explicit second parameter set less than DIM. "
           << "Other values should be set to zero. "
           << std::endl;
  int numVals = DIM / 2;
  QPoint pt4( arr, numVals);

  for(int dim=0; dim<numVals; ++dim)
      EXPECT_EQ(pt4[dim], arr[dim]);

  for(int dim=numVals+1; dim<DIM; ++dim)
      EXPECT_EQ(pt4[dim], CoordType() );

}


//------------------------------------------------------------------------------
TEST( quest_point, point_numericArray_constructor)
{
  static const int DIM = 5;
  typedef int CoordType;
  typedef primal::NumericArray<CoordType, DIM> QArray;
  typedef primal::Point<CoordType, DIM> QPoint;

  // Set elt i of input array to i
  CoordType arr[DIM];
  for(int dim=0; dim<DIM; ++dim)
      arr[dim] = dim;

  //
  std::cout<<"\nQuest: testing constructor that copies entire array. "
           << "Default second parameter of constructor is DIM."
           << std::endl;
  QArray arr1( arr );
  QPoint pt(arr);

  for(int dim=0; dim<DIM; ++dim)
      EXPECT_EQ(pt[dim], arr[dim]);
}


TEST( quest_point, point_copy_and_assignment)
{
  static const int DIM = 5;
  typedef int CoordType;
  typedef primal::Point<CoordType, DIM> QPoint;

  // Set elt i of input array to i
  CoordType arr[DIM];
  for(int dim=0; dim<DIM; ++dim)
      arr[dim] = dim;
  QPoint ptOrig( arr );

  //
  std::cout<<"\nQuest: testing copy constructor" << std::endl;
  QPoint ptCopy1( ptOrig );
  QPoint ptCopy2 = ptOrig;

  for(int dim=0; dim<DIM; ++dim)
  {
      EXPECT_EQ(ptOrig[dim], ptCopy1[dim]);
      EXPECT_EQ(ptOrig[dim], ptCopy2[dim]);
  }


  //
  std::cout<<"\nQuest: testing assignment operator" << std::endl;
  QPoint ptAssign(5);
  ptAssign = ptOrig;
  for(int dim=0; dim<DIM; ++dim)
  {
      EXPECT_EQ(ptOrig[dim], ptAssign[dim]);
  }
}

TEST( quest_point, point_equality)
{
  static const int DIM = 5;
  typedef int CoordType;
  typedef primal::Point<CoordType, DIM> QPoint;

  // Set elt i of input array to i
  CoordType arr[DIM];
  for(int dim=0; dim<DIM; ++dim)
      arr[dim] = dim;
  QPoint ptOrig( arr );

  //
  std::cout<<"\nQuest: testing equality of same point" << std::endl;
  QPoint ptCopy1( ptOrig );

  EXPECT_TRUE(ptOrig == ptCopy1);
  EXPECT_FALSE(ptOrig != ptCopy1);


  //
  std::cout<<"\nQuest: testing inequality of different points" << std::endl;
  QPoint ptDifferent( 7 );
  EXPECT_FALSE(ptOrig == ptDifferent);
  EXPECT_TRUE(ptOrig != ptDifferent);

  //
  std::cout<<"\n Testing that zero() and ones() point are equal to their constructor counterparts"
          << std::endl;
  EXPECT_EQ(QPoint::zero(), QPoint());
  EXPECT_EQ(QPoint::zero(), QPoint(0));
  EXPECT_EQ(QPoint::ones(), QPoint(1));
}


TEST( quest_point, point_to_array)
{
  static const int DIM = 5;
  typedef int CoordType;
  typedef primal::Point<CoordType, DIM> QPoint;

  // Set elt i of input array to i
  CoordType arr[DIM];
  for(int dim=0; dim<DIM; ++dim)
      arr[dim] = dim;
  QPoint pt(arr);


  CoordType outputArr[DIM];
  pt.to_array(outputArr);

  for(int dim=0; dim<DIM; ++dim)
      EXPECT_EQ(arr[dim], outputArr[dim] );

}


TEST( quest_point, point_make_point)
{
  static const int DIM = 3;
  typedef int CoordType;
  typedef primal::Point<CoordType, DIM> QPoint;

  const int x = 10;
  const int y = 20;
  const int z = 30;

  std::cout<<"\nQuest: Testing make_point with two coordinates.  Third should be set to 0" << std::endl;
  QPoint pt2 = QPoint::make_point(x,y);
  EXPECT_EQ(pt2[0], x );
  EXPECT_EQ(pt2[1], y );
  EXPECT_EQ(pt2[2], 0 );

  //
  std::cout<<"\nQuest: Testing make_point with three coordinates." << std::endl;
  QPoint pt3 = QPoint::make_point(x,y,z);
  EXPECT_EQ(pt3[0], x );
  EXPECT_EQ(pt3[1], y );
  EXPECT_EQ(pt3[2], z );

}

TEST( quest_point, point_midpoint)
{
  static const int DIM = 3;
  typedef int CoordType;
  typedef primal::Point<CoordType, DIM> QPoint;

  QPoint p10(10);
  QPoint p30(30);
  QPoint p50(50);

  EXPECT_TRUE(p30 == QPoint::midpoint(p10,p50));

}

TEST( quest_point, point_linear_interpolation)
{
  static const int DIM = 3;
  typedef int CoordType;
  typedef primal::Point<CoordType, DIM> QPoint;

  QPoint p0(0);
  QPoint p1(100);

  EXPECT_TRUE(QPoint::lerp(p0,p1, 0) == p0);
  EXPECT_TRUE(QPoint::lerp(p0,p1, 1) == p1);
  EXPECT_TRUE(QPoint::lerp(p0,p1, 0.5) == QPoint::midpoint(p0,p1));
  EXPECT_TRUE(QPoint::lerp(p0,p1, .25) == QPoint(25));
  EXPECT_TRUE(QPoint::lerp(p0,p1, .75) == QPoint(75));


}
//----------------------------------------------------------------------
//----------------------------------------------------------------------
#include "slic/UnitTestLogger.hpp"
using asctoolkit::slic::UnitTestLogger;

int main(int argc, char * argv[])
{
  int result = 0;

  ::testing::InitGoogleTest(&argc, argv);

  UnitTestLogger logger;  // create & initialize test logger,

  // finalized when exiting main scope

  result = RUN_ALL_TESTS();

  return result;
}


