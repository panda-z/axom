/*
 * Copyright (c) 2015, Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 *
 * All rights reserved.
 *
 * This source code cannot be distributed without permission and further
 * review from Lawrence Livermore National Laboratory.
 */


/**
 * \file IndirectionSet.hpp
 *
 * \brief A few indirection set classes
 */

#ifndef MESHAPI_INDIRECTION_SET_H_
#define MESHAPI_INDIRECTION_SET_H_

#include <cstddef>
#include <vector>

#include "meshapi/OrderedSet.hpp"

namespace asctoolkit {
namespace meshapi {


/**
 * \class
 *
 * \brief Concrete class (all template parameters fixed) for an array-based indirection set
 */
  class ArrayIndirectionSet : public OrderedSet< policies::RuntimeSizeHolder<Set::PositionType>
                                               , policies::ZeroOffset<Set::PositionType>
                                               , policies::StrideOne<Set::PositionType>
                                               , policies::ArrayIndirection<Set::PositionType, Set::ElementType>
                                               >
  {
  private:
      typedef OrderedSet< policies::RuntimeSizeHolder<Set::PositionType>
      , policies::ZeroOffset<Set::PositionType>
      , policies::StrideOne<Set::PositionType>
      , policies::ArrayIndirection<Set::PositionType, Set::ElementType>
      >  OrderedSetType;

  public:
      typedef OrderedSetType::PositionType PositionType;
      typedef OrderedSetType::IndexType IndexType;
      typedef OrderedSetType::ElementType ElementType;

  private:
      static const PositionType DEFAULT_SIZE = OrderedSetType::SizePolicyType::DEFAULT_VALUE;
      static const PositionType DEFAULT_OFFSET = OrderedSetType::OffsetPolicyType::DEFAULT_VALUE;
      static const PositionType DEFAULT_STRIDE = OrderedSetType::StridePolicyType::DEFAULT_VALUE;

  public:
      ArrayIndirectionSet (PositionType size = DEFAULT_SIZE)
          : OrderedSetType(size, DEFAULT_OFFSET, DEFAULT_STRIDE) {}
    ~ArrayIndirectionSet () {}
  };

  /**
   * \class
   *
   * \brief Concrete class (all template parameters fixed) for an STL vector-based indirection set
   */
  class VectorIndirectionSet : public OrderedSet< policies::RuntimeSizeHolder<Set::PositionType>
                                               , policies::ZeroOffset<Set::PositionType>
                                               , policies::StrideOne<Set::PositionType>
                                               , policies::STLVectorIndirection<Set::PositionType, Set::ElementType>
                                               // add parent subset ?
                                               >
  {
  private:
      typedef OrderedSet< policies::RuntimeSizeHolder<Set::PositionType>
      , policies::ZeroOffset<Set::PositionType>
      , policies::StrideOne<Set::PositionType>
      , policies::STLVectorIndirection<Set::PositionType, Set::ElementType>
      >  OrderedSetType;

      typedef OrderedSet::IndirectionPolicyType IndirectionPolicyType;

  public:
      typedef OrderedSetType::PositionType PositionType;
      typedef OrderedSetType::IndexType IndexType;
      typedef OrderedSetType::ElementType ElementType;

      typedef IndirectionPolicyType::VectorType ArrType;
  private:
      static const PositionType DEFAULT_SIZE = OrderedSetType::SizePolicyType::DEFAULT_VALUE;
      static const PositionType DEFAULT_OFFSET = OrderedSetType::OffsetPolicyType::DEFAULT_VALUE;
      static const PositionType DEFAULT_STRIDE = OrderedSetType::StridePolicyType::DEFAULT_VALUE;

  public:
      VectorIndirectionSet (PositionType size = DEFAULT_SIZE)
          : OrderedSetType(size, DEFAULT_OFFSET, DEFAULT_STRIDE) {}

    ~VectorIndirectionSet () {}
  };


} // end namespace meshapi
} // end namespace asctoolkit

#endif //  MESHAPI_INDIRECTION_SET_H_
