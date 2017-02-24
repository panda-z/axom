/*
 * Copyright (c) 2017, Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 *
 * All rights reserved.
 *
 * This source code cannot be distributed without permission and further
 * review from Lawrence Livermore National Laboratory.
 */

#ifndef VIRTUALGRID_HPP_
#define VIRTUALGRID_HPP_

#include "common/CommonTypes.hpp"
#include "slic/slic.hpp"

#include "quest/BoundingBox.hpp"
#include "quest/Point.hpp"


// C/C++ includes
#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>
#include <stdio.h>


namespace quest {

//NDIMS IS EITHER 2 or 3
template< typename T, int NDIMS >
class VirtualGrid
{
public:

  typedef BoundingBox< double, NDIMS > BoxType;
  typedef Point< double, NDIMS > PointType;

public:

  VirtualGrid(const PointType& origin, const double * spacing, const int * res);
  VirtualGrid(const double * origin, const double * spacing, const int * res);
  ~VirtualGrid();
    
  int getBinIndex(const PointType & pt);
  int getNumBins();
  bool binEmpty(int index);
  std::vector<T>& getBinContents(int index);
  const std::vector<T>& getBinContents(int index) const;
  void clear(int index);
  void insert(const BoxType& BB, const T& obj);

  const static int INVALID_BIN_INDEX = -1;

protected:

  VirtualGrid();
    
private:

  PointType m_origin;
  double m_spacing[NDIMS];
  int m_resolution[NDIMS];

  void addObj(const T& obj, int index);
  bool isValidIndex(int index) const;

  struct Bin {
    std::vector<T> ObjectArray;
    //other stuff
  };
  std::vector<Bin> m_bins;

  DISABLE_COPY_AND_ASSIGNMENT(VirtualGrid);
  DISABLE_MOVE_AND_ASSIGNMENT(VirtualGrid);

};//end class

}//end namespace quest

namespace quest
{

template< typename T, int NDIMS >
VirtualGrid< T, NDIMS >::VirtualGrid()
{

  SLIC_ASSERT((NDIMS == 3) || (NDIMS == 2));
    
  size_t newsize = 1;
  for (int i=0; i<NDIMS; ++i) {
    m_origin[i] = 0;
    m_spacing[i] = 1.0;
    m_resolution[i] = 100;
    newsize *= 100;
  }

  m_bins.resize(newsize);
}

template< typename T, int NDIMS >
VirtualGrid< T, NDIMS >::VirtualGrid(const PointType& origin,
                                     const double * step,
                                     const int * res)
{
  SLIC_ASSERT(step != ATK_NULLPTR);
  SLIC_ASSERT(res != ATK_NULLPTR);
  SLIC_ASSERT((NDIMS == 3) || (NDIMS == 2));

  size_t newsize = 1;
  for (int i=0; i<NDIMS;++i) {
    m_origin[i] = origin[i];

    SLIC_ASSERT(step[i] !=0 );
    m_spacing[i] = step[i];
    m_resolution[i] = res[i];
    newsize *= res[i];
  }

  m_bins.resize(newsize);
}

template< typename T, int NDIMS >
VirtualGrid< T, NDIMS >::VirtualGrid(const double * origin,
                                     const double * step,
                                     const int * res)
{
  SLIC_ASSERT(origin != ATK_NULLPTR);
  SLIC_ASSERT(step != ATK_NULLPTR);
  SLIC_ASSERT(res != ATK_NULLPTR);
  SLIC_ASSERT((NDIMS == 3) || (NDIMS == 2));

  size_t newsize = 1;
  for (int i=0; i<NDIMS;++i) {
    m_origin[i] = origin[i];
    
    SLIC_ASSERT(step[i] !=0 );
    m_spacing[i] = step[i];
    m_resolution[i] = res[i];
    newsize *= res[i];
  }

  m_bins.resize(newsize);
}

template< typename T, int NDIMS >
VirtualGrid< T, NDIMS >::~VirtualGrid()
{
}

template< typename T, int NDIMS >
int VirtualGrid<T, NDIMS>::getBinIndex(const PointType & pt)
{
  SLIC_ASSERT((NDIMS == 3) || (NDIMS == 2));

  int retval = 0;
  for (int i = 0; i < NDIMS; ++i) {
    int tmp = (pt[i] - m_origin[i]) / m_spacing[i];

    if (tmp < 0 || tmp >= m_resolution[i]) {
      return INVALID_BIN_INDEX;
    }

    int factor = 1;
    for (int j = 0; j < i; ++j) {
      factor *= m_resolution[j];
    }

    retval += tmp * factor;
  }

  return retval;
}

template< typename T, int NDIMS >
bool VirtualGrid<T, NDIMS>::isValidIndex(int index) const
{
  return index >=0 && index < static_cast<int>(m_bins.size());
}

template< typename T, int NDIMS >
int VirtualGrid<T, NDIMS>::getNumBins()
{
  return m_bins.size();
}

template< typename T, int NDIMS >
bool VirtualGrid<T, NDIMS>::binEmpty(int index)
{
  if (!isValidIndex(index)) {
    return true;
  }

  return m_bins[index].ObjectArray.empty();
}

template< typename T, int NDIMS >
std::vector<T>& VirtualGrid<T, NDIMS>::getBinContents(int index)
{
  SLIC_ASSERT(isValidIndex(index));

  return m_bins[index].ObjectArray;
}

template< typename T, int NDIMS >
const std::vector<T>& VirtualGrid<T, NDIMS>::getBinContents(int index) const
{
  SLIC_ASSERT(isValidIndex(index));

  return m_bins[index].ObjectArray;
}

template< typename T, int NDIMS >
void VirtualGrid<T, NDIMS>::clear(int index)
{
  if (isValidIndex(index)) {
    m_bins[index].ObjectArray.clear();
  }
}

template< typename T, int NDIMS >
void VirtualGrid<T, NDIMS>::addObj(const T& obj, int index)
{
  SLIC_CHECK(!isValidIndex(index));

  if (isValidIndex(index)) {
    m_bins[index].ObjectArray.push_back(obj);
  }
}


//WIP For NDIMS == 3, NDIMS == 2 is same but needs to be added
// by removing the k case and z_length
template< typename T, int NDIMS>
void VirtualGrid<T, NDIMS>::insert(const BoxType& BB,
                                  const T& obj)
{
  SLIC_ASSERT((NDIMS == 3) || (NDIMS == 2));
  PointType min, max;
   
  min = BB.getMin();
  max = BB.getMax();   
    
  PointType tempx = PointType::make_point(max[0], min[1], min[2]);
  PointType tempy = PointType::make_point(min[0], max[1], min[2]);
  PointType tempz = PointType::make_point(max[0], min[1], max[2]);
   
  int start = getBinIndex(min);
  //  SLIC_INFO("Minimum is "<< start);
  //  SLIC_INFO("Getting xlength with tempx"<<tempx);

  int xlength = (getBinIndex(tempx)- start);
  //    SLIC_INFO("Getting end index "<<getBinIndex(tempx));
  //SLIC_INFO("Getting x and y res");

  int x_res = m_resolution[0];
  int y_res = m_resolution[1];
   
  //    SLIC_INFO("Getting x and y res"<<x_res<<"and "<<y_res);
  int ylength = (getBinIndex(tempy) / x_res) - ( start / x_res);
  int zlength = (getBinIndex(tempz) / (x_res * y_res)) - (start / (x_res*y_res));


  //   SLIC_INFO("Lengths"<<xlength<<"and "<<ylength<<"and "<<zlength);


  //int end = getBinIndex(max);
    
  for (int k=0; k<= zlength; ++k) {
    for (int j=0; j<=ylength; ++j) {
      for (int i=0; i<=xlength; ++i) {
	// SLIC_INFO("Adding object at index " <<
        //           start + i + (j * x_res) + (k * x_res * y_res)) ;
        addObj(obj, start + i + (j * x_res) + (k * x_res * y_res));
      }
    }
  }
}

}  /* end namespace quest */


#endif /* VIRTUALGRID_HPP_ */


