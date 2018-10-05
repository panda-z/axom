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

/*!
 * \file
 *
 * \brief Consists of utility functions to facilitate in test development.
 */
// Axom includes
#include "axom/core/Macros.hpp"

// Mint includes
#include "axom/mint/config.hpp"

#include "axom/mint/mesh/CurvilinearMesh.hpp"
#include "axom/mint/mesh/Mesh.hpp"
#include "axom/mint/mesh/MeshTypes.hpp"
#include "axom/mint/mesh/ParticleMesh.hpp"
#include "axom/mint/mesh/RectilinearMesh.hpp"
#include "axom/mint/mesh/UniformMesh.hpp"
#include "axom/mint/mesh/UnstructuredMesh.hpp"

// Slic includes
#include "axom/slic.hpp"

// gtest includes
#include "gtest/gtest.h" // for gtest

namespace axom
{
namespace mint
{

//------------------------------------------------------------------------------
template < int MeshType >
struct mesh_type_name
{
  static constexpr char* name() { return (char*)"[UNDEFINED]"; };
};

//------------------------------------------------------------------------------
template < >
struct mesh_type_name< STRUCTURED_UNIFORM_MESH >
{
  static constexpr char* name() { return (char*)"STRUCTURED_UNIFORM_MESH"; };
};

//------------------------------------------------------------------------------
template < >
struct mesh_type_name< STRUCTURED_CURVILINEAR_MESH >
{
  static constexpr char* name() {
    return (char*)"STRUCTURED_CURVILINEAR_MESH";
  };
};

//------------------------------------------------------------------------------
template < >
struct mesh_type_name< STRUCTURED_RECTILINEAR_MESH >
{
  static constexpr char* name() {
    return (char*)"STRUCTURED_RECTILINEAR_MESH";
  };
};

//------------------------------------------------------------------------------
template < >
struct mesh_type_name< UNSTRUCTURED_MESH >
{
  static constexpr char* name() { return (char*)"UNSTRUCTURED_MESH"; };
};

//------------------------------------------------------------------------------
template < >
struct mesh_type_name< UNSTRUCTURED_SINGLE_SHAPE_MESH >
{
  static constexpr char* name() { return (char*)"UNSTRUCTURED_SINGLE_SHAPE_MESH"; };
};

//------------------------------------------------------------------------------
template < >
struct mesh_type_name< UNSTRUCTURED_MIXED_SHAPE_MESH >
{
  static constexpr char* name() { return (char*)"UNSTRUCTURED_MIXED_SHAPE_MESH"; };
};

//------------------------------------------------------------------------------
template < >
struct mesh_type_name< PARTICLE_MESH>
{
  static constexpr char* name() { return (char*)"PARTICLE_MESH"; };
};

/*!
 * \brief Creates a mesh of type MeshType equivalent to the given uniform mesh.
 *
 * \param [in]  uniform_mesh the specified uniform mesh.
 * \param [out] output mesh pointer to the output mesh, created by this method.
 *
 * \tparam MeshType the output mesh type
 *
 * \note This method is specialized for each mesh type.
 *
 * \note The caller must deallocate the returned mesh object.
 */
/// @{
template < int MeshType=STRUCTURED_UNIFORM_MESH >
Mesh* create_mesh( const UniformMesh& uniform_mesh )
{
  const int dimension = uniform_mesh.getDimension();

  double lo[3];
  double hi[3];
  IndexType N[3] = { -1, -1, -1};
  for ( int i=0 ; i < dimension ; ++i )
  {
    N[ i ]  = uniform_mesh.getNodeResolution( i );
    lo[ i ] = uniform_mesh.evaluateCoordinate(0,i);
    hi[ i ] = uniform_mesh.evaluateCoordinate( N[i]-1, i );
  }
  UniformMesh* output_mesh = new UniformMesh( lo, hi, N[0], N[1], 
                                                          N[2] );

  EXPECT_EQ( output_mesh->getMeshType(), STRUCTURED_UNIFORM_MESH );
  EXPECT_EQ( output_mesh->getDimension(), uniform_mesh.getDimension() );
  EXPECT_EQ( output_mesh->getNumberOfNodes(), uniform_mesh.getNumberOfNodes() );
  EXPECT_EQ( output_mesh->getNumberOfCells(), uniform_mesh.getNumberOfCells() );

  return output_mesh;
}

//------------------------------------------------------------------------------
template < >
Mesh* create_mesh< STRUCTURED_CURVILINEAR_MESH >(
                                        const UniformMesh& uniform_mesh )
{
  const int dimension = uniform_mesh.getDimension();
  IndexType node_dims[] = { -1, -1, -1 };

  for ( int i=0 ; i < dimension ; ++i )
  {
    node_dims[ i ] = uniform_mesh.getNodeResolution( i );
  }

  CurvilinearMesh* output_mesh = new CurvilinearMesh( 
                                               node_dims[ I_DIRECTION ],
                                               node_dims[ J_DIRECTION ],
                                               node_dims[ K_DIRECTION ] );

  const IndexType numNodes = uniform_mesh.getNumberOfNodes();
  for ( IndexType inode=0 ; inode < numNodes ; ++inode )
  {
    double pt[ 3 ];
    uniform_mesh.getNode( inode, pt );

    for ( int idim=0 ; idim < dimension ; ++idim )
    {
      double* coord_array = output_mesh->getCoordinateArray( idim );
      SLIC_ASSERT( coord_array != nullptr );

      coord_array[ inode ] = pt[ idim ];
    }

  } // END for all nodes

  EXPECT_EQ( output_mesh->getMeshType(), STRUCTURED_CURVILINEAR_MESH );
  EXPECT_EQ( output_mesh->getDimension(), uniform_mesh.getDimension() );
  EXPECT_EQ( output_mesh->getNumberOfNodes(), uniform_mesh.getNumberOfNodes() );
  EXPECT_EQ( output_mesh->getNumberOfCells(), uniform_mesh.getNumberOfCells() );

  return output_mesh;
}

//------------------------------------------------------------------------------
template < >
Mesh* create_mesh< STRUCTURED_RECTILINEAR_MESH >(
                                         const UniformMesh& uniform_mesh )
{
  const int dimension = uniform_mesh.getDimension();
  SLIC_ASSERT( dimension >= 1 );

  IndexType node_dims[] = { -1, -1, -1 };
  for ( int i=0 ; i < dimension ; ++i )
  {
    node_dims[ i ] = uniform_mesh.getNodeResolution( i );
  }

  RectilinearMesh* output_mesh = new RectilinearMesh(
                                               node_dims[ I_DIRECTION ],
                                               node_dims[ J_DIRECTION ],
                                               node_dims[ K_DIRECTION ] );

  IndexType Ni = uniform_mesh.getNodeResolution( I_DIRECTION );
  double* x = output_mesh->getCoordinateArray( X_COORDINATE );
  SLIC_ASSERT( x != nullptr );
  for ( IndexType i=0 ; i < Ni ; ++i )
  {
    x[ i ] = uniform_mesh.evaluateCoordinate( i, I_DIRECTION );
  } // END for all i

  if ( dimension >= 2 )
  {
    // fill y
    double* y = output_mesh->getCoordinateArray( Y_COORDINATE );
    SLIC_ASSERT( y != nullptr );

    IndexType Nj = uniform_mesh.getNodeResolution( J_DIRECTION );
    for ( IndexType j=0 ; j < Nj ; ++j )
    {
      y[ j ] = uniform_mesh.evaluateCoordinate( j, J_DIRECTION );
    } // END for all j

  }

  if ( dimension == 3 )
  {
    // fill z
    double* z = output_mesh->getCoordinateArray( Z_COORDINATE );
    SLIC_ASSERT( z != nullptr );

    const IndexType Nk =
      uniform_mesh.getNodeResolution( K_DIRECTION );
    for ( IndexType k=0 ; k < Nk ; ++k )
    {
      z[ k ] = uniform_mesh.evaluateCoordinate( k, K_DIRECTION );
    } // END for all k

  } // END if 3-D

  EXPECT_EQ( output_mesh->getMeshType(), STRUCTURED_RECTILINEAR_MESH );
  EXPECT_EQ( output_mesh->getDimension(), uniform_mesh.getDimension() );
  EXPECT_EQ( output_mesh->getNumberOfNodes(), uniform_mesh.getNumberOfNodes() );
  EXPECT_EQ( output_mesh->getNumberOfCells(), uniform_mesh.getNumberOfCells() );

  return output_mesh;
}

//------------------------------------------------------------------------------
template < >
Mesh* create_mesh< PARTICLE_MESH >( 
                                        const UniformMesh& uniform_mesh )
{
  const int dimension            = uniform_mesh.getDimension();
  const IndexType numNodes = uniform_mesh.getNumberOfNodes();

  ParticleMesh* output_mesh = 
                                  new ParticleMesh( dimension, numNodes );

  for ( IndexType inode=0 ; inode < numNodes ; ++inode )
  {
    double node[ 3 ];
    uniform_mesh.getNode( inode, node );

    for ( int idim=0 ; idim < dimension ; ++idim )
    {
      double* coord = output_mesh->getCoordinateArray( idim );
      SLIC_ASSERT( coord != nullptr );

      coord[ inode ] = node[ idim ];
    }

  } // END for all nodes

  EXPECT_EQ( output_mesh->getMeshType(), PARTICLE_MESH );
  EXPECT_EQ( output_mesh->getDimension(), uniform_mesh.getDimension() );
  EXPECT_EQ( output_mesh->getNumberOfNodes(), uniform_mesh.getNumberOfNodes() );
  EXPECT_EQ( output_mesh->getNumberOfCells(), uniform_mesh.getNumberOfNodes() );

  return output_mesh;
}

//------------------------------------------------------------------------------
template < >
Mesh* 
create_mesh< UNSTRUCTURED_SINGLE_SHAPE_MESH >( 
                                        const UniformMesh& uniform_mesh )
{
  const int dimension            = uniform_mesh.getDimension();
  const IndexType numNodes = uniform_mesh.getNumberOfNodes();
  const IndexType numCells = uniform_mesh.getNumberOfCells();

  using UnstructuredMeshType = UnstructuredMesh< SINGLE_SHAPE >;
  CellType cell_type   = ( dimension==3 ) ? HEX :
                               ( (dimension==2) ? QUAD : SEGMENT );

  UnstructuredMeshType* output_mesh = 
          new UnstructuredMeshType( dimension, cell_type, numNodes, numCells );

  // append nodes
  for ( IndexType inode=0 ; inode < numNodes ; ++inode )
  {
    double node[ 3 ];
    uniform_mesh.getNode( inode, node );
    output_mesh->appendNodes( node );
  }

  // append cells
  for ( IndexType icell=0 ; icell < numCells ; ++icell )
  {
    IndexType cell[ 8 ];
    uniform_mesh.getCellNodeIDs( icell, cell );
    output_mesh->appendCell( cell, cell_type );
  }

  EXPECT_EQ( output_mesh->getMeshType(), UNSTRUCTURED_MESH );
  EXPECT_EQ( output_mesh->getDimension(), uniform_mesh.getDimension() );
  EXPECT_EQ( output_mesh->getNumberOfNodes(), uniform_mesh.getNumberOfNodes() );
  EXPECT_EQ( output_mesh->getNumberOfCells(), uniform_mesh.getNumberOfCells() );

  return output_mesh;
}

//------------------------------------------------------------------------------
template < >
Mesh* 
create_mesh< UNSTRUCTURED_MIXED_SHAPE_MESH >( 
                                        const UniformMesh& uniform_mesh )
{
  const int dimension            = uniform_mesh.getDimension();
  const IndexType numNodes = uniform_mesh.getNumberOfNodes();
  const IndexType numCells = uniform_mesh.getNumberOfCells();
  const IndexType k_node_res = uniform_mesh.getNodeResolution( K_DIRECTION );
  const IndexType j_node_res = uniform_mesh.getNodeResolution( J_DIRECTION );
  const IndexType i_node_res = uniform_mesh.getNodeResolution( I_DIRECTION );

  using UnstructuredMeshType = UnstructuredMesh< MIXED_SHAPE >;

  IndexType node_capacity = numNodes;
  IndexType cell_capacity = numCells * 1.6;

  if ( dimension == 3 )
  {
    node_capacity = numNodes + numCells / 1.75;
    cell_capacity = numCells * 3.75;
  }

  UnstructuredMeshType* output_mesh = new UnstructuredMeshType( dimension,
                                                                node_capacity,
                                                                cell_capacity );

  // append nodes
  for ( IndexType nodeID = 0 ; nodeID < numNodes ; ++nodeID )
  {
    double node[ 3 ];
    uniform_mesh.getNode( nodeID, node );
    output_mesh->appendNodes( node );
  }

  // append cells
  if ( dimension == 1 )
  {
    IndexType cell[ 2 ];
    for ( IndexType cellID=0 ; cellID < numCells ; ++cellID )
    {
      uniform_mesh.getCellNodeIDs( cellID, cell );
      output_mesh->appendCell( cell, SEGMENT );
    }
  }
  else if ( dimension == 2 )
  {
    IndexType uniformCell[ 4 ];
    IndexType triangle[3];
    for ( IndexType j = 0 ; j < j_node_res - 1 ; ++j )
    {
      for ( IndexType i = 0 ; i < i_node_res - 1 ; ++i )
      {
        uniform_mesh.getCellNodeIDs( i, j, uniformCell );

        if ( (i + j) % 2 == 0 )
        {
          output_mesh->appendCell( uniformCell, QUAD);
        }
        else
        {
          triangle[0] = uniformCell[0];
          triangle[1] = uniformCell[1];
          triangle[2] = uniformCell[2];
          output_mesh->appendCell( triangle, TRIANGLE );

          triangle[0] = uniformCell[2];
          triangle[1] = uniformCell[3];
          triangle[2] = uniformCell[0];
          output_mesh->appendCell( triangle, TRIANGLE );
        }
      }
    }
  }
  else
  {
    const double* spacing = uniform_mesh.getSpacing();
    IndexType uniformCell[ 8 ];
    IndexType pyramid[5];
            for ( IndexType k = 0 ; k < k_node_res - 1 ; ++k )
    {
      for ( IndexType j = 0 ; j < j_node_res - 1 ; ++j )
      {
        for ( IndexType i = 0 ; i < i_node_res - 1 ; ++i )
        {
          uniform_mesh.getCellNodeIDs( i, j, k, uniformCell );

          if ( (i + j + k) % 2 == 0 )
          {
            output_mesh->appendCell( uniformCell, HEX );
          }
          else
          {
            const IndexType centerNode = output_mesh->getNumberOfNodes();
            const double centroid[3] = { (i + 0.5) * spacing[ 0 ],
                                         (j + 0.5) * spacing[ 1 ],
                                         (k + 0.5) * spacing[ 2 ] };
            output_mesh->appendNodes( centroid );

            pyramid[0] = uniformCell[0]; 
            pyramid[1] = uniformCell[1];
            pyramid[2] = uniformCell[2];
            pyramid[3] = uniformCell[3];
            pyramid[4] = centerNode;
            output_mesh->appendCell( pyramid, PYRAMID );

            pyramid[0] = uniformCell[4]; 
            pyramid[1] = uniformCell[7];
            pyramid[2] = uniformCell[6];
            pyramid[3] = uniformCell[5];
            output_mesh->appendCell( pyramid, PYRAMID );

            pyramid[0] = uniformCell[1]; 
            pyramid[1] = uniformCell[5];
            pyramid[2] = uniformCell[6];
            pyramid[3] = uniformCell[2];
            output_mesh->appendCell( pyramid, PYRAMID );

            pyramid[0] = uniformCell[0]; 
            pyramid[1] = uniformCell[3];
            pyramid[2] = uniformCell[7];
            pyramid[3] = uniformCell[4];
            output_mesh->appendCell( pyramid, PYRAMID );

            pyramid[0] = uniformCell[0]; 
            pyramid[1] = uniformCell[4];
            pyramid[2] = uniformCell[5];
            pyramid[3] = uniformCell[1];
            output_mesh->appendCell( pyramid, PYRAMID );

            pyramid[0] = uniformCell[3]; 
            pyramid[1] = uniformCell[2];
            pyramid[2] = uniformCell[6];
            pyramid[3] = uniformCell[7];
            output_mesh->appendCell( pyramid, PYRAMID );
          }
        }
      }
    }
  }

  EXPECT_EQ( output_mesh->getMeshType(), UNSTRUCTURED_MESH );
  EXPECT_EQ( output_mesh->getDimension(), uniform_mesh.getDimension() );

  return output_mesh;
}
/// @}

} /* namespace mint */
} /* namespace axom */

