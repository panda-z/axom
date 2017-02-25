/*
 * Copyright (c) 2015, Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 *
 * All rights reserved.
 *
 * This source code cannot be distributed without permission and further
 * review from Lawrence Livermore National Laboratory.
 */


#ifndef NUMERIC_ARRAY_HPP_
#define NUMERIC_ARRAY_HPP_

#include "common/ATKMacros.hpp"
#include "slic/slic.hpp"

// C/C++ includes
#include <cstring>    // For memcpy()
#include <algorithm>  // For std:: copy and fill
#include <ostream>    // For print() and operator <<

namespace {

  /*!
   *****************************************************************************
   * \brief Utility function that clamps an input val to a given range.
   * \param [in] val  The value to clamp
   * \param [in] lower The lower range
   * \param [in] upper The upper range
   * \return The clamped value.
   * \post lower <= returned value <= upper.
   *****************************************************************************
   */
  template< typename T >
  T clampVal( T val, T lower, T upper )
  {
    SLIC_ASSERT( lower <= upper);
    return std::min( std::max( val, lower), upper);
  }

}

namespace axom {
namespace primal {

// Forward declare the templated classes and operator functions
template< typename T, int NDIMS >
class NumericArray;

/// \name Forward Declared Overloaded Operators
///@{

/*!
 *******************************************************************************
 * \brief Checks if two numeric arrays are component-wise equal.
 * \param [in] lhs numeric array instance on the left-hand side.
 * \param [in] rhs numeric array instance on the right-hand side.
 * \return status true if lhs==rhs, otherwise, false.
 *******************************************************************************
 */
template < typename T,int NDIMS >
bool operator==( const NumericArray< T,NDIMS >& lhs,
                 const NumericArray< T,NDIMS >& rhs );

/*!
 *******************************************************************************
 * \brief Checks if two numeric arrays are *not* component-wise equal.
 * \param [in] lhs numeric array instance on the left-hand side.
 * \param [in] rhs numeric array instance on the right-hand side.
 * \return status true if lhs!=rhs, otherwise, false.
 *******************************************************************************
 */
template < typename T,int NDIMS >
bool operator!=( const NumericArray< T,NDIMS >& lhs,
                 const NumericArray< T,NDIMS >& rhs);

/*!
 *******************************************************************************
 * \brief Performs component-wise addition of two numeric arrays.
 * \param [in] lhs numeric array instance on the left-hand side.
 * \param [in] rhs numeric array instance on the right-hand side.
 * \return C resulting numeric array from the component-wise addition.
 *******************************************************************************
 */
template < typename T,int NDIMS >
NumericArray< T,NDIMS > operator+ ( const NumericArray< T,NDIMS >& lhs,
                                    const NumericArray< T,NDIMS >& rhs  );

/*!
 *******************************************************************************
 * \brief Performs component-wise subtraction of two numeric arrays.
 * \param [in] lhs numeric array instance on the left-hand side.
 * \param [in] rhs numeric array instance on the right-hand side.
 * \result C resulting numeric array from component-wise subtraction.
 *******************************************************************************
 */
template < typename T,int NDIMS >
NumericArray< T,NDIMS > operator-( const NumericArray< T,NDIMS >& lhs,
                                   const NumericArray< T,NDIMS >& rhs  );

/*!
 * \brief Forward declaration for NumericArray's (unary) negation
 */
template<typename T, int DIM> NumericArray<T,DIM> operator-(const NumericArray<T, DIM> & lhs, const NumericArray<T, DIM> & rhs);

/*!
 *******************************************************************************
 * \brief Scalar multiplication a numeric array; Scalar on rhs.
 * \param [in] arr numeric array instance.
 * \param [in] scalar user-supplied scalar.
 * \return C resutling numeric array, \f$ \ni: C_i = scalar*arr_i, \forall i\f$
 *******************************************************************************
 */
template < typename T,int NDIMS >
NumericArray< T,NDIMS > operator*( const NumericArray<T, NDIMS> & arr,
                                   double scalar );

/*!
 *******************************************************************************
 * \brief Scalar multiplication a numeric array; Scalar on lhs.
 * \param [in] scalar user-supplied scalar.
 * \param [in] arr numeric array instance.
 * \return C resulting numeric array, \f$ \ni: C_i = scalar*arr_i, \forall i\f$
 *******************************************************************************
 */
template < typename T,int NDIMS >
NumericArray< T,NDIMS > operator*( double scalar,
                                   const NumericArray<T, NDIMS> & arr );

/*!
 *******************************************************************************
 * \brief Component-wise multiplication of NumericArrays
 * \param [in] lhs numeric array instance on the left-hand side.
 * \param [in] rhs numeric array instance on the right-hand side.
 * \return C resulting numeric array, \f$ \ni: C_i = lhs_i * rhs_i, \forall i\f$
 *******************************************************************************
 */
template < typename T,int NDIMS >
NumericArray< T,NDIMS > operator*( const NumericArray<T, NDIMS> & lhs,
                                   const NumericArray<T, NDIMS> & rhs  );

/*!
 *******************************************************************************
 * \brief Component-wise division of NumericArrays
 * \param [in] lhs numeric array instance on the left-hand side.
 * \param [in] rhs numeric array instance on the right-hand side.
 * \return C resulting numeric array, \f$ \ni: C_i = lhs_i / rhs_i, \forall i\f$
 * \pre \f$ rhs_i != 0.0, \forall i \f$
 *******************************************************************************
 */
template < typename T,int NDIMS >
NumericArray< T,NDIMS > operator/( const NumericArray<T, NDIMS> & lhs,
                                   const NumericArray<T, NDIMS> & rhs  );

/*!
 *******************************************************************************
 * \brief Scalar division of NumericArray; Scalar on rhs
 * \param [in] arr numeric array instance
 * \param [in] scalar user-supplied scalar
 * \return C resulting numeric array, \f$ \ni: C_i = arr_i/scalar, \forall i\f$
 * \pre scalar != 0.0
 *******************************************************************************
 */
template < typename T,int NDIMS >
NumericArray< T,NDIMS > operator/( const NumericArray<T, NDIMS>& arr,
                                   double scalar );

/*!
 *******************************************************************************
 * \brief Overloaded output operator for numeric arrays
 * \param [in] os C++ output stream
 * \param [in] arr numeric array instance.
 *******************************************************************************
 */
template < typename T,int NDIMS >
std::ostream& operator<<( std::ostream & os,
                          const NumericArray<T,NDIMS> & arr );

///@}


/**
 * \brief Type trait to avoid outputting chars when a value is expected
 *  This avoids unintentionally outputting system beeps
 */
template < typename T >
struct NonChar
{
  typedef T type;     /** The non-char type to return */
};

template < >
struct NonChar<char>
{
  /** A non-char signed type to which we can cast a char for output */
  typedef int type;
};

template < >
struct NonChar < unsigned char >
{
  /** A non-char unsigned type to which we can cast a char for output */
  typedef unsigned int type;
};


/*!
 *******************************************************************************
 * \class NumericArray
 *
 * \brief A simple statically sized array of data with component-wise operators
 *******************************************************************************
 */
template < typename T,int NDIMS >
class NumericArray
{
public:
    enum {
      NBYTES = NDIMS*sizeof(T)
    };

public:

    // -- TODO: Add static_assert that T has numeric type --

  /*!
   *****************************************************************************
   * \brief Fill the first sz coordinates with val and zeros the rest
   * \param [in] val The value to set the coordinates to. Defaults to zero.
   * \param [in] sz The number of components to set to val.
   * The rest will be set to zero.  Defaults is NDIMS.
   * If sz is greater than NDIMS, we set all coordinates to val
   *****************************************************************************
   */
  explicit NumericArray( T val = T(), int sz = NDIMS);

  /*!
   *****************************************************************************
   * \brief Creates a numeric array from the first sz values of the input array.
   * \param [in] vals An array containing at least sz values
   * \param [in] sz number of coordinates. Defaults to NDIMS.
   * \note If sz is greater than NDIMS, we only take the first NDIMS values.
   *****************************************************************************
   */
  NumericArray( T* vals, int sz = NDIMS);

  /*!
   *****************************************************************************
   * \brief Copy constructor.
   * \param [in] other The numeric array to copy
   *****************************************************************************
   */
  NumericArray( const NumericArray& other ) { *this = other; };

  /*!
   *****************************************************************************
   * \brief Destructor.
   *****************************************************************************
   */
   ~NumericArray() { }

  /*!
   *****************************************************************************
   * \brief Returns the dimension of this numeric array instance.
   * \return d the dimension (size) of the array
   * \post d >= 1.
   *****************************************************************************
   */
  int dimension() const { return NDIMS; };

  /*!
   *****************************************************************************
   * \brief Assignment operator.
   * \param [in] rhs a numeric array instance on the right hand side.
   *****************************************************************************
   */
  NumericArray& operator=(const NumericArray& rhs);

  /*!
   *****************************************************************************
   * \brief Access operator for individual components.
   * \param [in] i the component index to access
   * \return \f$ p_i \f$ the value at the given component index.
   * \pre \f$  0 \le i < NDIMS \f$
   *****************************************************************************
   */
  const T& operator[](int i) const;
  T& operator[](int i);

  /*!
   *****************************************************************************
   * \brief Returns a pointer to the underlying data.
   *****************************************************************************
   */
  const T* data() const;
  T* data();

  /*!
   *
   *****************************************************************************
   * \brief Copy the coordinate data to the provided array
   * \param [in] arr The array to which we are copying.
   * \pre The user needs to make sure that the provided array has been allocated
   * and has sufficient space for NDIMS coordinates.
   *****************************************************************************
   */
  void to_array(T* arr) const;

  /*!
   *****************************************************************************
   * \brief Simple formatted print of a numeric array instance
   * \param os The output stream to write to
   * \return A reference to the modified ostream
   *****************************************************************************
   */
  std::ostream& print(std::ostream& os) const;

  /*!
   *****************************************************************************
   * \brief Component-wise addition assignment operator.
   * \param [in] arr the array to add.
   * Adds the numeric array arr to this instance (component-wise).
   * \return A reference to the NumericArray instance after addition.
   *****************************************************************************
   */
  NumericArray< T,NDIMS >& operator+=( const NumericArray< T,NDIMS >& arr );

  /*!
   *****************************************************************************
   * \brief Component-wise subtraction assignment operator.
   * \param [in] arr the array to subtract.
   * Subtracts the numeric array arr from this instance (component-wise).
   * \return A reference to the NumericArray instance after subtraction.
   *****************************************************************************
   */
  NumericArray< T,NDIMS >& operator-=( const NumericArray< T,NDIMS >& arr );

 /*!
  *****************************************************************************
  * \brief Scalar multiplication on the NumericArray instance.
  * \param [in] scalar the scalar value with which to multiply.
  * Each element of the numeric array is multiplied by scalar
  * \return A reference to the NumericArray instance after scalar multiplication.
  *****************************************************************************
  */
 NumericArray< T,NDIMS >& operator*=(double scalar);

 /*!
  *****************************************************************************
  * \brief Scalar division on the NumericArray instance.
  * \param [in] scalar the scalar value with which to divide .
  * \pre scalar != 0
  * Each element of the numeric array is divided by scalar
  * \return A reference to the NumericArray instance after scalar division.
  *****************************************************************************
  */
 NumericArray< T,NDIMS >& operator/=(double scalar);

 /*!
  *****************************************************************************
  * \brief Component-wise multiplication assignment operator.
  * \param [in] arr the array to multiply (component-wise).
  * Multiplies the numeric array arr with this instance (component-wise).
  * \return A reference to the NumericArray instance after cwise multiplication.
  *****************************************************************************
  */
 NumericArray< T,NDIMS >& operator*=( const NumericArray< T,NDIMS >& arr );

 /*!
  *****************************************************************************
  * \brief Component-wise division assignment operator.
  * \param [in] arr the array to divide (component-wise).
  * Divides the numeric array arr with this instance (component-wise).
  * \pre forall i, arr[i] != 0
  * \return A reference to the NumericArray instance after cwise division.
  *****************************************************************************
  */
 NumericArray< T,NDIMS >& operator/=( const NumericArray< T,NDIMS >& arr );

 /*!
  *****************************************************************************
  * \brief Ensures that the highest value of the coordinates is at most upperVal.
  * \param [in] upperVal The highest possible value
  * \post forall i, arr[i] <= upperVal
  * \return A reference to the NumericArray instance after clamping upper
  *****************************************************************************
  */
 NumericArray< T,NDIMS >& clampUpper( const T& upperVal);

 /*!
  *****************************************************************************
  * \brief Ensures that the lowest value of the coordinates is at least lowerVal.
  * \param [in] lowerVal The lowest possible value
  * \post forall i, arr[i] >= lowerVal
  * \return A reference to the NumericArray instance after clamping lower
  *****************************************************************************
  */
 NumericArray< T,NDIMS >& clampLower( const T& lowerVal);

 /*!
  *****************************************************************************
  * \brief Ensures that each coordinate's value is in range [lowerVal,upperVal].
  * \param [in] lowerVal The lowest possible value
  * \param [in] upperVal The highest possible value
  * \pre lowerVal <= upperVal
  * \post forall i, lowerVal <= arr[i] <= upperVal
  * \return A reference to the NumericArray instance after clamping
  *****************************************************************************
  */
 NumericArray< T,NDIMS >& clamp( const T& lowerVal, const T& upperVal);


 /*!
  *****************************************************************************
  * \brief Find the max component.
  * \return The value of the largest component.
  *****************************************************************************
  */
 T max() const;

 /*!
  *****************************************************************************
  * \brief Find the min component.
  * \return The value of the smallest component.
  *****************************************************************************
  */
 T min() const;

 /*!
  *****************************************************************************
  * \brief Find the index of the max component.
  * \return The index of the largest component ( \f$ 0 \le ret < NDIMS \f$)
  *****************************************************************************
  */
 int argMax() const;

 /*!
  *****************************************************************************
  * \brief Find the index of the min component.
  * \return The index of the smallest component ( \f$ 0 \le ret < NDIMS \f$)
  *****************************************************************************
  */
 int argMin() const;

private:
  void verifyIndex(int ATK_DEBUG_PARAM(idx)) const
  {
      SLIC_ASSERT(idx >= 0 && idx < NDIMS);
  }

protected:
  T m_components[ NDIMS ];    /*! The encapsulated array */
};

} /* namespace primal */

} /* namespace axom */


//------------------------------------------------------------------------------
//  NumericArray implementation
//------------------------------------------------------------------------------

namespace axom {
namespace primal {

//------------------------------------------------------------------------------
template < typename T, int NDIMS >
NumericArray< T,NDIMS >::NumericArray(T val, int sz)
{
  // NOTE (KW): This should be a static assert in the class
  SLIC_ASSERT( NDIMS >= 1 );

  // Fill first nvals coordinates with val ( 0 <= nvals <= NDIMS )
  const int nvals = ::clampVal(sz, 0, NDIMS);
  std::fill( m_components, m_components+nvals, val );

  // Fill any remaining coordinates with zero
  if ( nvals < NDIMS ) {
    std::fill( m_components+nvals, m_components+NDIMS, T() );
  }
}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
NumericArray< T, NDIMS >::NumericArray(T* vals, int sz)
{
  SLIC_ASSERT( NDIMS >= 1 );

  const int nvals = ::clampVal(sz, 0, NDIMS);

  // Copy first nvals coordinates from vals array ( 0 <= nvals <= NDIMS )
  std::copy( vals, vals+nvals, m_components);

  // Fill any remaining coordinates with zero
  if ( nvals < NDIMS) {
    std::fill( m_components+nvals, m_components+NDIMS, T());
  }

}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
inline NumericArray< T,NDIMS >&
NumericArray< T,NDIMS >::operator=( const NumericArray<T,NDIMS>& rhs )
{

  if( this == &rhs ) {
    return *this;
  }

  // copy all the data
  memcpy( m_components, rhs.m_components, NBYTES);
  return *this;
}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
inline T& NumericArray< T,NDIMS >::operator[](int i)
{
    verifyIndex(i);
    return m_components[ i ];
}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
inline const T& NumericArray< T,NDIMS >::operator[](int i) const
{
  verifyIndex(i);
  return m_components[ i ];
}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
inline const T* NumericArray< T,NDIMS >::data() const
{
  return m_components;
}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
inline T* NumericArray< T,NDIMS >::data()
{
  return m_components;
}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
void NumericArray< T,NDIMS >::to_array(T* arr) const
{
  SLIC_ASSERT( arr != ATK_NULLPTR);
  memcpy( arr, m_components, NBYTES );
}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
std::ostream& NumericArray< T, NDIMS >::print(std::ostream& os) const
{
  os <<"[ ";
  for (int dim=0; dim < NDIMS -1; ++dim) {
     os << static_cast< typename NonChar<T>::type >( m_components[dim] )
        << " ";
  }

  os << static_cast<typename NonChar<T>::type>(m_components[NDIMS-1]) << "]";

  return os;
}

//------------------------------------------------------------------------------
// Member function arithmetic operators (component-wise)
//------------------------------------------------------------------------------

template < typename T,int NDIMS >
inline NumericArray< T,NDIMS >&
NumericArray< T,NDIMS >::operator*=( double scalar )
{
    for ( int i=0; i < NDIMS; ++i ) {
       m_components[ i ] *= scalar;
    }

    return *this;
}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
inline NumericArray< T,NDIMS >&
NumericArray< T,NDIMS >::operator/=( double scalar )
{
    SLIC_ASSERT(scalar != 0.);
    return operator*=( 1./scalar );
}

//------------------------------------------------------------------------------
template < typename T, int NDIMS >
inline NumericArray< T,NDIMS >&
NumericArray< T,NDIMS >::operator*=(const NumericArray<T,NDIMS>& v)
{
  for ( int i=0; i < NDIMS; ++i ) {
     m_components[ i ] *=  v[ i ];
  }

  return *this;
}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
inline NumericArray<  T,NDIMS >&
NumericArray< T,NDIMS >::operator/=( const NumericArray< T,NDIMS >& v )
{
  for ( int i=0; i < NDIMS; ++i ) {
     SLIC_ASSERT( v[ i ] != 0.);
     m_components[ i ] /=  v[ i ];
  }

  return *this;
}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
inline NumericArray< T,NDIMS >&
NumericArray< T,NDIMS >::operator+=(const NumericArray< T,NDIMS >& v)
{
  for ( int i=0; i < NDIMS; ++i ) {
     m_components[ i ] +=  v[ i ];
  }

  return *this;
}

//------------------------------------------------------------------------------
template < typename T, int NDIMS >
inline NumericArray< T, NDIMS >&
NumericArray< T,NDIMS >::operator-=(const NumericArray<T,NDIMS>& v)
{
  for ( int i=0; i < NDIMS; ++i ) {
     m_components[ i ] -= v[ i ];
  }

  return *this;
}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
inline NumericArray< T, NDIMS >&
NumericArray< T,NDIMS >::clamp( const T& lowerVal, const T& upperVal )
{
    SLIC_ASSERT( lowerVal <= upperVal);

    for ( int i=0; i < NDIMS; ++i ) {
       m_components[ i ] = std::min( std::max( m_components[ i ],lowerVal),
                                               upperVal);
    }

    return *this;
}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
inline NumericArray< T,NDIMS >&
NumericArray< T,NDIMS >::clampLower( const T& lowerVal)
{
    for ( int i=0; i < NDIMS; ++i ) {
       m_components[ i ] = std::max( m_components[ i ], lowerVal);
    }

    return *this;
}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
inline NumericArray< T,NDIMS >&
NumericArray< T,NDIMS >::clampUpper( const T& upperVal)
{
    for ( int i=0; i < NDIMS; ++i ) {
       m_components[ i ] = std::min( m_components[ i ], upperVal);
    }

    return *this;
}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
inline T NumericArray< T,NDIMS >::max() const
{
  T result = this->m_components[0];
  for ( int i=1; i < NDIMS; ++i ) {

    T tmp = m_components[i];

    if ( tmp > result) {
      result = tmp;
    }

  }

  return result;
}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
inline T NumericArray< T,NDIMS >::min() const
{
  T result = this->m_components[0];
  for ( int i=1; i < NDIMS; ++i ) {
     T tmp = this->m_components[i];

     if ( tmp < result) {
       result = tmp;
     }

  }

  return result;
}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
inline int NumericArray< T,NDIMS >::argMax() const
{
  int idx = 0;
  for ( int i=1; i < NDIMS; ++i ) {
    if ( m_components[i] > m_components[idx]) {
      idx = i;
    }
  }

  return idx;
}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
inline int NumericArray< T,NDIMS >::argMin() const
{
  int idx = 0;
  for ( int i=1; i < NDIMS; ++i ) {
     if ( m_components[i] < m_components[idx] ) {
       idx = i;
     }
  }

  return idx;
}

//------------------------------------------------------------------------------
/// Free functions implementing comparison and arithmetic operators
//------------------------------------------------------------------------------

template < typename T,int NDIMS >
bool operator==( const NumericArray< T,NDIMS >& lhs,
                 const NumericArray< T,NDIMS >& rhs)
{
  for ( int dim=0; dim < NDIMS; ++dim ) {
     if ( lhs[dim] != rhs[dim] ) {
       return false;
     }
  }

  return true;
}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
bool operator!=( const NumericArray< T,NDIMS >& lhs,
                 const NumericArray< T,NDIMS >& rhs)
{
  return !(lhs == rhs);
}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
std::ostream& operator<<(std::ostream & os, const NumericArray<T,NDIMS> & arr)
{
  arr.print(os);
  return os;
}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
inline NumericArray< T,NDIMS > operator*( const NumericArray<T,NDIMS>& arr,
                                        double scalar)
{
  NumericArray< T,NDIMS > result(arr);
  result *=scalar;
  return result;
}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
inline NumericArray< T,NDIMS > operator*( double scalar,
                                        const NumericArray<T,NDIMS>& arr)
{
  NumericArray< T, NDIMS > result(arr);
  result *=scalar;
  return result;
}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
inline NumericArray<T,NDIMS> operator+( const NumericArray<T,NDIMS>& lhs,
                                        const NumericArray<T,NDIMS>& rhs)
{
  NumericArray< T, NDIMS > result(lhs);
  result += rhs;
  return result;
}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
inline NumericArray< T,NDIMS > operator*( const NumericArray<T,NDIMS>& lhs,
                                          const NumericArray<T,NDIMS>& rhs)
{
  NumericArray< T,NDIMS > result(lhs);
  result *= rhs;
  return result;
}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
inline NumericArray< T,NDIMS > operator/( const NumericArray<T,NDIMS>& lhs,
                                          const NumericArray<T,NDIMS>& rhs)
{
  NumericArray< T,NDIMS > result(lhs);
  result /= rhs;
  return result;
}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
inline NumericArray<T,NDIMS> operator/( const NumericArray<T,NDIMS>& arr,
                                        double scalar)
{
  NumericArray< T, NDIMS > result(arr);
  result /=scalar;
  return result;
}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
inline NumericArray<T,NDIMS> operator-( const NumericArray<T,NDIMS>& lhs,
                                        const NumericArray<T,NDIMS>& rhs)
{
  NumericArray< T,NDIMS > result(lhs);
  result -= rhs;
  return result;
}

//------------------------------------------------------------------------------
template < typename T,int NDIMS >
inline NumericArray<T,NDIMS> operator-(const NumericArray<T,NDIMS>& arr)
{
  NumericArray< T, NDIMS > result;
  result -= arr;
  return result;
}


} /* namespace primal*/

} /* namespace axom */

#endif /* NUMERIC_ARRAY_HXX_ */
