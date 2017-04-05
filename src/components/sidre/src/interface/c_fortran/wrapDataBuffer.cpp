// wrapDataBuffer.cpp
// This is generated code, do not edit
//
// Copyright (c) 2015, Lawrence Livermore National Security, LLC.
// Produced at the Lawrence Livermore National Laboratory.
//
// All rights reserved.
//
// This source code cannot be distributed without permission and
// further review from Lawrence Livermore National Laboratory.
//
// wrapDataBuffer.cpp
#include "wrapDataBuffer.h"
#include "sidre/DataBuffer.hpp"
#include "sidre/SidreTypes.hpp"

extern "C" {
namespace axom
{
namespace sidre
{

SIDRE_IndexType SIDRE_databuffer_get_index(const SIDRE_databuffer * self)
{
  const DataBuffer * SH_this =
    static_cast<const DataBuffer *>(static_cast<const void *>(self));
// splicer begin class.DataBuffer.method.get_index
  IndexType SH_rv = SH_this->getIndex();
  return SH_rv;
// splicer end class.DataBuffer.method.get_index
}

size_t SIDRE_databuffer_get_num_views(const SIDRE_databuffer * self)
{
  const DataBuffer * SH_this =
    static_cast<const DataBuffer *>(static_cast<const void *>(self));
// splicer begin class.DataBuffer.method.get_num_views
  size_t SH_rv = SH_this->getNumViews();
  return SH_rv;
// splicer end class.DataBuffer.method.get_num_views
}

void SIDRE_databuffer_describe(SIDRE_databuffer * self, int type,
                               SIDRE_SidreLength num_elems)
{
  DataBuffer * SH_this = static_cast<DataBuffer *>(static_cast<void *>(self));
// splicer begin class.DataBuffer.method.describe
  SH_this->describe(getTypeID(type), num_elems);
  return;
// splicer end class.DataBuffer.method.describe
}

void SIDRE_databuffer_allocate_existing(SIDRE_databuffer * self)
{
  DataBuffer * SH_this = static_cast<DataBuffer *>(static_cast<void *>(self));
// splicer begin class.DataBuffer.method.allocate_existing
  SH_this->allocate();
  return;
// splicer end class.DataBuffer.method.allocate_existing
}

void SIDRE_databuffer_allocate_from_type(SIDRE_databuffer * self, int type,
                                         SIDRE_SidreLength num_elems)
{
  DataBuffer * SH_this = static_cast<DataBuffer *>(static_cast<void *>(self));
// splicer begin class.DataBuffer.method.allocate_from_type
  SH_this->allocate(getTypeID(type), num_elems);
  return;
// splicer end class.DataBuffer.method.allocate_from_type
}

void SIDRE_databuffer_reallocate(SIDRE_databuffer * self,
                                 SIDRE_SidreLength num_elems)
{
  DataBuffer * SH_this = static_cast<DataBuffer *>(static_cast<void *>(self));
// splicer begin class.DataBuffer.method.reallocate
  SH_this->reallocate(num_elems);
  return;
// splicer end class.DataBuffer.method.reallocate
}

void * SIDRE_databuffer_get_void_ptr(SIDRE_databuffer * self)
{
  DataBuffer * SH_this = static_cast<DataBuffer *>(static_cast<void *>(self));
// splicer begin class.DataBuffer.method.get_void_ptr
  void * SH_rv = SH_this->getVoidPtr();
  return SH_rv;
// splicer end class.DataBuffer.method.get_void_ptr
}

int SIDRE_databuffer_get_type_id(const SIDRE_databuffer * self)
{
  const DataBuffer * SH_this =
    static_cast<const DataBuffer *>(static_cast<const void *>(self));
// splicer begin class.DataBuffer.method.get_type_id
  TypeID SH_rv = SH_this->getTypeID();
  return static_cast<int>(SH_rv);
// splicer end class.DataBuffer.method.get_type_id
}

size_t SIDRE_databuffer_get_num_elements(const SIDRE_databuffer * self)
{
  const DataBuffer * SH_this =
    static_cast<const DataBuffer *>(static_cast<const void *>(self));
// splicer begin class.DataBuffer.method.get_num_elements
  size_t SH_rv = SH_this->getNumElements();
  return SH_rv;
// splicer end class.DataBuffer.method.get_num_elements
}

size_t SIDRE_databuffer_get_total_bytes(const SIDRE_databuffer * self)
{
  const DataBuffer * SH_this =
    static_cast<const DataBuffer *>(static_cast<const void *>(self));
// splicer begin class.DataBuffer.method.get_total_bytes
  size_t SH_rv = SH_this->getTotalBytes();
  return SH_rv;
// splicer end class.DataBuffer.method.get_total_bytes
}

size_t SIDRE_databuffer_get_bytes_per_element(const SIDRE_databuffer * self)
{
  const DataBuffer * SH_this =
    static_cast<const DataBuffer *>(static_cast<const void *>(self));
// splicer begin class.DataBuffer.method.get_bytes_per_element
  size_t SH_rv = SH_this->getBytesPerElement();
  return SH_rv;
// splicer end class.DataBuffer.method.get_bytes_per_element
}

void SIDRE_databuffer_print(const SIDRE_databuffer * self)
{
  const DataBuffer * SH_this =
    static_cast<const DataBuffer *>(static_cast<const void *>(self));
// splicer begin class.DataBuffer.method.print
  SH_this->print();
  return;
// splicer end class.DataBuffer.method.print
}

// splicer begin class.DataBuffer.additional_functions
// splicer end class.DataBuffer.additional_functions

}  // namespace axom
}  // namespace sidre
}  // extern "C"
