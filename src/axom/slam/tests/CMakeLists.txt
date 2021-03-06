# Copyright (c) 2017-2021, Lawrence Livermore National Security, LLC and
# other Axom Project Developers. See the top-level COPYRIGHT file for details.
#
# SPDX-License-Identifier: (BSD-3-Clause)
#------------------------------------------------------------------------------
# Slam unit tests
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# Specify list of tests
#------------------------------------------------------------------------------

set(gtest_slam_tests
    # test sets
    slam_set_Set.cpp
    slam_set_NullSet.cpp
    slam_set_PositionSet.cpp
    slam_set_RangeSet.cpp
    slam_set_IndirectionSet.cpp
    slam_set_BitSet.cpp
    slam_set_DynamicSet.cpp
    slam_set_Iterator.cpp

    # test relations
    slam_relation_StaticVariable.cpp
    slam_relation_StaticConstant.cpp
    slam_relation_DynamicVariable.cpp
    slam_relation_DynamicConstant.cpp

    # test maps
    slam_Map.cpp
    slam_map_SubMap.cpp
    slam_map_BivariateMap.cpp
    slam_map_DynamicMap.cpp

    # test integration of sets, relations and maps
    slam_AccessingRelationDataInMap.cpp

    # aux tests
    slam_ModularInt.cpp
    )


set(slam_tests_depends_on core slic slam gtest)

#------------------------------------------------------------------------------
# Add gtest based tests
#------------------------------------------------------------------------------
foreach(test ${gtest_slam_tests})
    get_filename_component( test_name ${test} NAME_WE )
    blt_add_executable( NAME ${test_name}_test
                        SOURCES ${test}
                        OUTPUT_DIR ${TEST_OUTPUT_DIRECTORY}
                        DEPENDS_ON ${slam_tests_depends_on}
                        FOLDER axom/slam/tests )
    axom_add_test( NAME ${test_name}
                   COMMAND ${test_name}_test )
endforeach()
